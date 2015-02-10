#ifndef SQLITE_H_
# define SQLITE_H_

#include "restsql.h"
#include <sqlite3.h>

class Sqlite
{
private:
	std::string database;
	sqlite3 *db;
	char *zErrMsg;
   	std::string query;
public:
	Sqlite(std::string, std::string);
	int exec();
   	int rc;
	std::string error_message;
   	std::vector<std::map<std::string, std::string> > result;
};

#endif