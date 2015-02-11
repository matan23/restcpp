#include "restsql.h"

using namespace std;

// static ITranslatable *list(request_t& request_st, tcp::socket& socket) {
// 	Json::Value root;   // will contains the root value after parsing
// 	Json::Reader reader;
	
// 	bool parsingSuccessful = reader.parse(request_st.content, root);
// 	if (!parsingSuccessful) {
// 		parse_error(reader);
// 		return NULL;
// 	}

// 	map<string, string> columns_key_value;
// 	for (Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {            
// 		std::string column_name = itr.key().asString();
// 		std::string column_value = (*itr).asString();

// 		columns_key_value[column_name.c_str()] = column_value;
// 	}

// 	std::string table;
// 	int id;

// 	istringstream (request_st.uri_args[1]) >> id;
// 	table = request_st.uri_args[0];

// 	return new Update(table, id, columns_key_value);
// }

// static ITranslatable *get(request_t& request_st, tcp::socket& socket) {
// 	Json::Value root;   // will contains the root value after parsing
// 	Json::Reader reader;
	
// 	bool parsingSuccessful = reader.parse(request_st.content, root);
// 	if (!parsingSuccessful) {
// 		parse_error(reader);
// 		return NULL;
// 	}

// 	map<string, string> columns_key_value;
// 	for (Json::ValueIterator itr = root.begin() ; itr != root.end() ; itr++ ) {            
// 		std::string column_name = itr.key().asString();
// 		std::string column_value = (*itr).asString();

// 		columns_key_value[column_name.c_str()] = column_value;
// 	}

// 	;
// 	std::string table;
// 	int id;

// 	istringstream (request_st.uri_args[1]) >> id;
// 	table = request_st.uri_args[0];

// 	return new Update(table, id, columns_key_value);
// }


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
		cout << "looks ok" << endl;
		// ITranslatable *updateQuery = exec_update(request_st, socket);

		// string database_name = string("dev");
		// Sqlite *db =  new Sqlite(database_name, updateQuery->translateToSqlQuery());
		// cout << db->exec() << "\n";
		// if (db->zErrMsg != NULL) {
		// 	std::string ret = "ERROR";
		// 	boost::system::error_code ignored_error;
	 //  		boost::asio::write(socket, boost::asio::buffer(ret), ignored_error);
		// } else {

			get_model(request_st, socket);		
		// }
	} else if (request_st.uri_args.size() == 1) {
		// cout << "looks ok" << endl;

		// ITranslatable *updateQuery = exec_update(request_st, socket);

		// string database_name = string("dev");
		// Sqlite *db =  new Sqlite(database_name, updateQuery->translateToSqlQuery());
		// cout << db->exec() << "\n";
		// if (db->zErrMsg != NULL) {
		// 	std::string ret = "ERROR";
		// 	boost::system::error_code ignored_error;
	 //  		boost::asio::write(socket, boost::asio::buffer(ret), ignored_error);
		// } else {
			get_list(request_st, socket);		
		// }
	} else {
		cout << "ERROR BAD URL" << endl;
	}
}