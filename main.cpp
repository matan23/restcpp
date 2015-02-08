#include "restsql.h"

using namespace std;

int	main(void) {


	string database_name = string("dev"); 
	string table_name = string("person");
	

// 
//
// Create table object
//
//	
	map<string, string> columns;
	columns["name"] = "text";
	columns["age"] = "int";

	ITranslatable *create_table = new CreateTable(table_name, columns);
	cout << create_table->translateToSqlQuery() << "\n";



// 
//
// Insert object
//
//	
	map<string, string> values;
	values["name"] = "Jero";
	values["age"] = "24";

	ITranslatable *insert = new Insert(table_name, values);
	cout << insert->translateToSqlQuery() << "\n";



// 
//
// Select object
//
//	
	ITranslatable *select = new Select(table_name);
	cout << select->translateToSqlQuery() << "\n";


// 
//
// SQLite !
//
//	

	Sqlite *db =  new Sqlite(database_name, create_table->translateToSqlQuery());
	cout << db->exec() << "\n";


	db =  new Sqlite(database_name, insert->translateToSqlQuery());
	cout << db->exec() << "\n";


	db =  new Sqlite(database_name, select->translateToSqlQuery());
	cout << db->exec() << "\n";

}