#include "restsql.h"
#include <map>

using namespace std;

void debug() {
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
	Sqlite *db;

	// db =  new Sqlite(database_name, create_table->translateToSqlQuery());
	// db->exec();


	// db = new Sqlite(database_name, insert->translateToSqlQuery());
	// db->exec();



	db = new Sqlite(database_name, select->translateToSqlQuery());
	db->exec();

	if(db->rc != SQLITE_OK){
		cout << "Error dammit : " + db->error_message << "\n";
	}
	else
	{
	   printf("Sql Result : \n");
	   for(int j = 0; j < db->result.size(); j++) {
	      printf("Row : %i\n", j);
	      for(std::map<string, string>::iterator itr = db->result[j].begin(), itr_end = db->result[j].end(); itr != itr_end; ++itr) {
	         cout << itr->first + " = " + itr->second + "\n";
	      }
	   }
	}



	ITranslatable *select_by_id = new Select(table_name, 2);
	cout << select_by_id->translateToSqlQuery() << "\n";


	db = new Sqlite(database_name, select_by_id->translateToSqlQuery());
	db->exec();

	if(db->rc != SQLITE_OK){
		cout << "Error dammit : " + db->error_message << "\n";
	}
	else
	{
	   printf("Sql Result : \n");
	   for(int j = 0; j < db->result.size(); j++) {
	      printf("Row : %i\n", j);
	      for(std::map<string, string>::iterator itr = db->result[j].begin(), itr_end = db->result[j].end(); itr != itr_end; ++itr) {
	         cout << itr->first + " = " + itr->second + "\n";
	      }
	   }
	}
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

int	main(void) {
	server();
}