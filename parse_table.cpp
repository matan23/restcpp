#include "restsql.h"

using namespace std;
using boost::asio::ip::tcp;

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

void	parse_table(request_t& request_st, tcp::socket& socket) {
	string database_name = string("dev"); 


	ITranslatable *create_table = parse_payload(request_st.content);

	cout << create_table->translateToSqlQuery() << "\n";	
	Sqlite *db =  new Sqlite(database_name, create_table->translateToSqlQuery());
	cout << db->exec() << "\n";
	if (db->zErrMsg != NULL) {
		std::string ret = "ERROR";
		boost::system::error_code ignored_error;
  		boost::asio::write(socket, boost::asio::buffer(ret), ignored_error);
	} else {
		std::string ret = "OK";
		boost::system::error_code ignored_error;
  		boost::asio::write(socket, boost::asio::buffer(ret), ignored_error);
	}
}