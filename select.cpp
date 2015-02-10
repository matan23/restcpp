#include "select.h"

using namespace std;

Select::Select(std::string table){
	this->table = table;
	this->id = 0;
}

Select::Select(std::string table, int id){
	this->table = table;
	this->id = id;
}

std::string Select::translateToSqlQuery() {
	string query;
	query = "SELECT * FROM " + this->table;

	if(this->id != 0)
	{
		query += " WHERE ID = " + to_string(this->id); 
	}

	query += ";";

	return query;
}