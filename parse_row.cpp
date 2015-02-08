#include "restsql.h"

using namespace std;

static ITranslatable *parse_payload(std::string &content) {
	Json::Value root;   // will contains the root value after parsing
	Json::Reader reader;
	
	bool parsingSuccessful = reader.parse(content, root);
	if (!parsingSuccessful) {
		parse_error(reader);
		return NULL;
	}

	map<string, string> columns_key_value;
	for (Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {            
		std::string column_name = itr.key().asString();
		std::string column_value = (*itr).asString();

		columns_key_value[column_name.c_str()] = column_value;
	}

	return new Insert("Person", columns_key_value);
}

void	parse_row(std::string &content) {
	string database_name = string("dev"); 


	ITranslatable *create_row = parse_payload(content);

	cout << create_row->translateToSqlQuery() << "\n";	
	Sqlite *db =  new Sqlite(database_name, create_row->translateToSqlQuery());
	cout << db->exec() << "\n";
	if (db->zErrMsg != NULL) {
		cout << db->zErrMsg;
	}
}