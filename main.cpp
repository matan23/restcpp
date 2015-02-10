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

	// Sqlite *db =  new Sqlite(database_name, create_table->translateToSqlQuery());
	// db->exec()


	Sqlite *db =  new Sqlite(database_name, insert->translateToSqlQuery());
	db->exec();

	if(db->rc != SQLITE_OK){
		cout << "Error dammit : " + db->error_message << "\n";
	}

	// db =  new Sqlite(database_name, select->translateToSqlQuery());
	// db->exec();


	// values["age"] = "25";
	// values["name"] = "Matan";
	// ITranslatable *update = new Update(table_name, 1, values);
	// cout << update->translateToSqlQuery() << "\n";

	// db =  new Sqlite(database_name, update->translateToSqlQuery());
	// db->exec();


	// db =  new Sqlite(database_name, select->translateToSqlQuery());
	// db->exec();


	// ITranslatable *del = new Delete(table_name, 1);
	// cout << del->translateToSqlQuery() << "\n";

	// db =  new Sqlite(database_name, del->translateToSqlQuery());
	// db->exec();


	// db =  new Sqlite(database_name, select->translateToSqlQuery());
	// db->exec();
	
}