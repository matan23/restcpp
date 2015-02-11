#ifndef SQLITE_H_
# define SQLITE_H_

#include "restsql.h"
#include <sqlite3.h>

class Sqlite
{
private:
	std::string database;
	sqlite3 *db;
   	std::vector<std::map<std::string, std::string>*> res;

	
   	std::string query;
public:
	int rc;
	std::string error_message;
	Sqlite(std::string, std::string);
	int exec();
	char *zErrMsg;
	std::vector<std::map<std::string, std::string> > result;
};

#endif