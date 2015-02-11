#include "restsql.h"

using namespace std;


static void parse_url(request_t& request_st, tcp::socket& socket) {
	string database_name = string("dev");
	std::string table;
	int id;

	istringstream (request_st.uri_args[1]) >> id;
	table = request_st.uri_args[0];

	ITranslatable *deleteQuery = new Delete(table, id);

	Sqlite *db =  new Sqlite(database_name, deleteQuery->translateToSqlQuery());
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

int	delete_method(request_t& request_st, tcp::socket& socket) {
	if (request_st.uri_args.size() == 2) {
		cout << "looks ok" << endl;

		parse_url(request_st, socket);
	} else {
		cout << "ERROR BAD URL" << endl;
	}
}