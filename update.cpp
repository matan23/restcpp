#include "update.h"

using namespace std;

Update::Update(string table, int id, map<string, string> values){
	this->table = table;
	this->id = id;
	this->values = values;
}

string Update::translateToSqlQuery() {
	string query;
	query = "UPDATE " + this->table + " SET ";

	for(std::map<string, string>::iterator itr = this->values.begin(), itr_end = this->values.end(); itr != itr_end; ++itr) {
		query += itr->first + " = '"  + itr->second + "', ";
	}
	query = query.substr(0, query.size()-2);
	
	query += " WHERE ID = " + to_string(this->id) + ";";

	return query;
}