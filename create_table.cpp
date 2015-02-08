#include "create_table.h"

using namespace std;

CreateTable::CreateTable(std::string name, std::map<std::string, std::string> columns){
	this->name = name;
	this->columns = columns;
}

std::string CreateTable::translateToSqlQuery() {
	string query;
	query = "CREATE TABLE " + this->name + " (";
	query += "ID INT PRIMARY KEY AUTOINCREMENT NOT NULL";

	for(std::map<string, string>::iterator itr = this->columns.begin(), itr_end = this->columns.end(); itr != itr_end; ++itr) {
		query += ", " + itr->first + " " + itr->second;
	}

	query += ");";

	return query;
}