#include "restsql.h"

using namespace std;
using boost::asio::ip::tcp;

static ITranslatable *parse_payload(std::string &content, std::string &error) {
	Json::Value root;   // will contains the root value after parsing
	Json::Reader reader;
	
	bool parsingSuccessful = reader.parse(content, root);
	if (!parsingSuccessful) {
		error = parse_error(reader);
		return NULL;
	}

	const Json::Value name = root["name"];
	const Json::Value columns = root["columns"];

	if (columns == "null" || columns.isObject() == false) {
		error = "expected column to be a hash";
		return NULL;
	}
	if (name == "null" || name.isString() == false) {
		error = "expected name to be a string";
		return NULL;	
	}

	map<string, string> columns_name;
	for (Json::ValueIterator itr = columns.begin() ; itr != columns.end() ; itr++ ) {            
		if (jsonIsSuppportedType(itr)) {
			std::string column_name = itr.key().asString();
			std::string column_value = (*itr).asString();

			columns_name[column_name.c_str()] = column_value;
		} else {
			error = "the json provided is probably malformatted json, please check documentation for supported payload";
			return NULL;
		}
	}
	if (columns_name.size() == 0) {
		error = "expected columns";
		return NULL;		
	}

	return new CreateTable(name.asString(), columns_name);
}

void	parse_table(request_t& request_st, __attribute__((unused))tcp::socket& socket) {
	string database_name = string("dev"); 
	std::string error = "";

	ITranslatable *create_table = parse_payload(request_st.content, error);

	if (create_table == NULL) {
		request_st.responseBuilder->answer400WithPayload(error);
		return;
	}

	cout << create_table->translateToSqlQuery() << "\n";	
	Sqlite *db =  new Sqlite(database_name, create_table->translateToSqlQuery());
	cout << db->exec() << "\n";
	
	if (db->error_message != "") {
		std::string error = db->error_message;
		std::cout << db->error_message;

		std::size_t found = error.find("already exists");
  		if (found != std::string::npos) {		
			request_st.responseBuilder->answer403(error);
		} else {		
			request_st.responseBuilder->answer500();		
		}
	} else {
		request_st.responseBuilder->answer200();		
	}
}