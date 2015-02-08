#include "insert.h"

using namespace std;

Insert::Insert(std::string table, std::map<std::string, std::string> values){
	this->table = table;
	this->values = values;
}

std::string Insert::translateToSqlQuery() {
	string query;
	query = "INSERT INTO " + this->table + " (";

	for(std::map<string, string>::iterator itr = this->values.begin(), itr_end = this->values.end(); itr != itr_end; ++itr) {
		query += itr->first + ", ";
	}
	query = query.substr(0, query.size()-2);
	
	query += ") VALUES (";

	for(std::map<string, string>::iterator itr = this->values.begin(), itr_end = this->values.end(); itr != itr_end; ++itr) {
		query += "'" + itr->second + "'" +", ";
	}
	query = query.substr(0, query.size()-2);
	
	query += ");";

	return query;
}