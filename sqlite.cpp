#include "sqlite.h"

using namespace std;

Sqlite::Sqlite(string database, string query)
{
	this->database = database;
	this->query = query;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int Sqlite::exec() {

   	int rc;
	/* Open database */

   rc = sqlite3_open((this->database + ".sqlite3").c_str(), &(this->db));
   if(rc){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Execute SQL statement */
   rc = sqlite3_exec(this->db, this->query.c_str(), callback, 0, &(this->zErrMsg));

   if(rc != SQLITE_OK){
   	fprintf(stderr, "SQL error: %s\n", this->zErrMsg);
    sqlite3_free(this->zErrMsg);
   }else{
      fprintf(stdout, "Success\n");
   }
   sqlite3_close(this->db);
   return 0;
}