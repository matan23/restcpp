#include "restsql.h"

using namespace std;

void	get_model(request_t& request_st, tcp::socket& socket) {
	string database_name = string("dev");
	std::string table;
	int id;

	istringstream (request_st.uri_args[1]) >> id;
	table = request_st.uri_args[0];

	ITranslatable *getQuery = new Select(table, id);

	Sqlite *db =  new Sqlite(database_name, getQuery->translateToSqlQuery());
	cout << getQuery->translateToSqlQuery() << "\n";
	cout << db->exec() << "\n";

	Json::Value response;	
	for(int j = 0; j < db->result.size(); j++) {
    	  printf("Row : %i\n", j);
      	for(std::map<string, string>::iterator itr = db->result[j].begin(), itr_end = db->result[j].end(); itr != itr_end; ++itr) {
        	 response[itr->first] = itr->second;
      	}
   	}

	Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	std::string output = writer.write(response);

	if (db->result.size() == 0) {
		request_st.responseBuilder->answer404();
	}
	else if (db->zErrMsg != NULL) {
		cout << db->zErrMsg;
		request_st.responseBuilder->answer400();
	} else {
		request_st.responseBuilder->answer200WithPayload(output);			
	}	
}

void	get_list(request_t& request_st, tcp::socket& socket) {
	string database_name = string("dev");
	ITranslatable *listQuery = new Select(request_st.uri_args[0]);

	Sqlite *db =  new Sqlite(database_name, listQuery->translateToSqlQuery());
	cout << listQuery->translateToSqlQuery() << "\n";
	cout << db->exec() << "\n";

	
	Json::Value responseVector;	
	for(int j = 0; j < db->result.size(); j++) {
    	  printf("Row : %i\n", j);
    	  Json::Value response;
      	for(std::map<string, string>::iterator itr = db->result[j].begin(), itr_end = db->result[j].end(); itr != itr_end; ++itr) {
        	 response[itr->first] = itr->second;
      	}
      	responseVector[j] = response;
   	}

	Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	std::string output = writer.write(responseVector);

	if (db->result.size() == 0) {
		request_st.responseBuilder->answer404();
	}
	else if (db->zErrMsg != NULL) {
		cout << db->zErrMsg;
		request_st.responseBuilder->answer400();
	} else {
		request_st.responseBuilder->answer200WithPayload(output);			
	}	
}

int	get_method(request_t& request_st, tcp::socket& socket) {
	if (request_st.uri_args.size() == 2) {
		get_model(request_st, socket);		
	} else if (request_st.uri_args.size() == 1) {		
		get_list(request_st, socket);		
	} else {
		cout << "ERROR BAD URL" << endl;
	}
}