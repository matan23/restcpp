#include "restsql.h"

using namespace std;

static ITranslatable *parse_payload(request_t& request_st) {
	Json::Value root;   // will contains the root value after parsing
	Json::Reader reader;
	
	bool parsingSuccessful = reader.parse(request_st.content, root);
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

	return new Insert(request_st.uri_args[0], columns_key_value);
}

void	parse_row(request_t& request_st, tcp::socket& socket) {
	string database_name = string("dev"); 
	string content = request_st.content;


	ITranslatable *create_row = parse_payload(request_st);

	cout << create_row->translateToSqlQuery() << "\n";	
	Sqlite *db =  new Sqlite(database_name, create_row->translateToSqlQuery());
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