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

	const Json::Value name = root["name"];
	const Json::Value columns = root["columns"];

	map<string, string> columns_name;
	for (Json::ValueIterator itr = columns.begin() ; itr != columns.end() ; itr++ ) {            
		std::string column_name = itr.key().asString();
		std::string column_value = (*itr).asString();

		columns_name[column_name.c_str()] = column_value;
	}

	return new CreateTable(name.asString(), columns_name);
}

void	parse_table(std::string &content) {
	ITranslatable *query = parse_payload(content);
	cout << query->translateToSqlQuery() << "\n";	
}