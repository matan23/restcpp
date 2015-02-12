#include "restsql.h"

using namespace std;

static ITranslatable *exec_update(string table, int id, string &content, string &error) {
	Json::Value root;   // will contains the root value after parsing
	Json::Reader reader;
	
	bool parsingSuccessful = reader.parse(content, root);
	if (!parsingSuccessful) {
		error = parse_error(reader);
		return NULL;
	}

	map<string, string> columns_key_value;
	for (Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {            

		if (jsonIsSuppportedType(itr)) {
			std::string column_name = itr.key().asString();
			std::string column_value = (*itr).asString();

			columns_key_value[column_name.c_str()] = column_value;
		} else {
			error = "the json provided is probably malformatted json, please check documentation for supported payload";
			return NULL;
		}
	}
	if (columns_key_value.size() == 0) {
		error = "expected values to update";
		return NULL;		
	}

	return new Update(table, id, columns_key_value);
}

int	put_method(request_t& request_st, __attribute__((unused))tcp::socket& socket) {
	std::string table;
	int id;

	if (request_st.uri_args.size() == 2) {

		if (!isInteger(request_st.uri_args[1])) {
			std::string url_error = "please provide an id for this ressource";
			request_st.responseBuilder->answer400WithPayload(url_error);
			return -1;
		}

		istringstream (request_st.uri_args[1]) >> id;
		table = request_st.uri_args[0];

		if (getNumberOfRows(table, id) == 0) {
			std::cout << "No row to update" << endl;
			request_st.responseBuilder->answer404();
			return -1;
		}

		string error = "";
		ITranslatable *updateQuery = exec_update(table, id, request_st.content, error);
		if (updateQuery == NULL) {		
			request_st.responseBuilder->answer400WithPayload(error);
			return -1;
		}

		string database_name = string("dev");
		Sqlite *db =  new Sqlite(database_name, updateQuery->translateToSqlQuery());
		cout << db->exec() << "\n";

		std::cout << "error is :" << db->error_message << endl;

		if (db->rc != SQLITE_OK && db->error_message != "") {
			std::string error = db->error_message;
			std::cout << db->error_message;

			std::size_t found = error.find("no such");
	  		if (found != std::string::npos) {		
				request_st.responseBuilder->answer400WithPayload(error);
			} else {		
				request_st.responseBuilder->answer500();		
			}
		} else {
			string location = "new data at";
			request_st.responseBuilder->answer200();
		}
	} else {
		request_st.responseBuilder->answer400();
	}
	return 0;
}