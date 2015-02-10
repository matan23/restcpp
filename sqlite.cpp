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
   // int i;
   // for(i=0; i<argc; i++){
   //    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   // }
   // printf("\n");
   Sqlite *sql = static_cast<Sqlite *>(db);

   std::map<std::string, std::string> new_line;

   for(int i=0; i<argc; i++)
   {
      new_line[azColName[i]] = argv[i];
   }

   // printf("\n\nRow : \n");
   // for(std::map<string, string>::iterator itr = new_line.begin(), itr_end = new_line.end(); itr != itr_end; ++itr) {
   //    cout << "column : " + itr->first + " value : " + itr->second + "\n";
   //    // printf("column : " + itr->first + "value : " + itr->second + "\n");
   // }
   
   sql->result.push_back(new_line);

   // printf("Sql Result : \n");
   // for(int j = 0; j < sql->result.size(); j++) {
   //    printf("Row : %i\n", j);
   //    for(std::map<string, string>::iterator itr = sql->result[j].begin(), itr_end = sql->result[j].end(); itr != itr_end; ++itr) {
   //       cout << itr->first + " = " + itr->second + "\n";
   //    }
   // }

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