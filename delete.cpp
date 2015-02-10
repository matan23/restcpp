#include "delete.h"

using namespace std;

Delete::Delete(string table, int id){
	this->table = table;
	this->id = id;
}

string Delete::translateToSqlQuery() {
	string query;
	query = "DELETE FROM " + this->table + " WHERE ID = " + to_string(this->id) + ";";

	return query;
}