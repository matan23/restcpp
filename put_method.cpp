#include "restsql.h"

using namespace std;

static ITranslatable *exec_update(request_t& request_st, tcp::socket& socket) {
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

	;
	std::string table;
	int id;

	istringstream (request_st.uri_args[1]) >> id;
	table = request_st.uri_args[0];

	return new Update(table, id, columns_key_value);
}

int	put_method(request_t& request_st, tcp::socket& socket) {
	if (request_st.uri_args.size() == 2) {
		cout << "looks ok" << endl;

		ITranslatable *updateQuery = exec_update(request_st, socket);

		string database_name = string("dev");
		Sqlite *db =  new Sqlite(database_name, updateQuery->translateToSqlQuery());
		cout << db->exec() << "\n";
		if (db->zErrMsg != NULL) {
			std::string ret = "ERROR";
			boost::system::error_code ignored_error;
	  		boost::asio::write(socket, boost::asio::buffer(ret), ignored_error);
		} else {
			request_st.responseBuilder->answer200();			
		}
	} else {
		request_st.responseBuilder->answer400();
	}
}