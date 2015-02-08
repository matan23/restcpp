#include "select.h"

using namespace std;

Select::Select(std::string table){
	this->table = table;
}

std::string Select::translateToSqlQuery() {
	string query;
	query = "SELECT * FROM " + this->table + ";";

	return query;
}