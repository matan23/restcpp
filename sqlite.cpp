#include "sqlite.h"

using namespace std;

Sqlite::Sqlite(string database, string query)
{
	this->database = database;
	this->query = query;
   this->error_message = "";
   this->zErrMsg = NULL;
}

static int callback(void *db, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");

   return 0;
}

int Sqlite::exec() {
	/* Open database */

   this->rc = sqlite3_open((this->database + ".sqlite3").c_str(), &(this->db));
   if(this->rc){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Execute SQL statement */
   this->rc = sqlite3_exec(this->db, this->query.c_str(), callback, (void*)this, &(this->zErrMsg));

   if(this->rc != SQLITE_OK){
   	fprintf(stderr, "SQL error: %s\n", this->zErrMsg);
      this->error_message.append(this->zErrMsg);
      sqlite3_free(this->zErrMsg);
   }else{
      fprintf(stdout, "Success\n");
   }
   sqlite3_close(this->db);
   return 0;
}