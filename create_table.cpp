#include "create_table.h"

using namespace std;

CreateTable::CreateTable(std::string name, std::map<std::string, std::string> columns){
	this->name = name;
	this->columns = columns;
}

std::string CreateTable::translateToSqlQuery() {
	string query;
	query = "CREATE TABLE " + this->name + " (";
	query += "ID INT PRIMARY KEY NOT NULL";

	for(std::map<string, string>::iterator itr = columns.begin(), itr_end = columns.end(); itr != itr_end; ++itr) {
		query += ", " + itr->first + " " + itr->second;
	}
	
	query += ");";

	return query;
}