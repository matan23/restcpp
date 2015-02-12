#include "restsql.h"

using namespace std;

static ITranslatable *parse_payload(request_t& request_st, string &error) {
	Json::Value root;   // will contains the root value after parsing
	Json::Reader reader;
	
	bool parsingSuccessful = reader.parse(request_st.content, root);
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
		error = "expected values to insert";
		return NULL;		
	}

	return new Insert(request_st.uri_args[0], columns_key_value);
}

void	parse_row(request_t& request_st, ATTR_UNUSED tcp::socket& socket) {
	string database_name = string("dev"); 
	string content = request_st.content;
	string error = "";

	ITranslatable *create_row = parse_payload(request_st, error);
	if (create_row == NULL) {		
		request_st.responseBuilder->answer400WithPayload(error);
		return;
	}

	cout << create_row->translateToSqlQuery() << "\n";	
	Sqlite *db =  new Sqlite(database_name, create_row->translateToSqlQuery());
	cout << db->exec() << "\n";

	if (db->error_message != "") {
		std::string error = db->error_message;
		std::cout << db->error_message;

		std::size_t found = error.find("no such");
  		if (found != std::string::npos) {		
			request_st.responseBuilder->answer404();
		} else if (error.find("has no column") != std::string::npos) {		
			request_st.responseBuilder->answer400WithPayload(error);
		} else {
			request_st.responseBuilder->answer500();		
		}
	} else {
		string location = "new data at";
		request_st.responseBuilder->answer201(location);		
	}
}