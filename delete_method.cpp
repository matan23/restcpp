#include "restsql.h"

using namespace std;

int	delete_method(request_t& request_st, ATTR_UNUSED tcp::socket& socket) {
	string database_name = string("dev");
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

		cout << "looks ok" << endl;

		ITranslatable *deleteQuery = new Delete(table, id);

		if (getNumberOfRows(table, id) == 0) {
			std::cout << "No row to delete" << endl;
			request_st.responseBuilder->answer404();
			return -1;
		}
		
		Sqlite *db =  new Sqlite(database_name, deleteQuery->translateToSqlQuery());
		cout << db->exec() << "\n";

		if (db->rc != SQLITE_OK && db->error_message != "") {
			std::string error = db->error_message;
			std::cout << db->error_message;

			std::size_t found = error.find("no such");
	  		if (found != std::string::npos) {		
				request_st.responseBuilder->answer404();
			} else {		
				request_st.responseBuilder->answer500();		
			}
		} else {
			request_st.responseBuilder->answer200();			
		}
	} else {
		request_st.responseBuilder->answer400();
	}
	return 0;
}