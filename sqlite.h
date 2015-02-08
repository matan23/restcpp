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
   	std::vector<std::map<std::string, std::string>*> res;

	
   	std::string query;
public:
	Sqlite(std::string, std::string);
	int exec();
	char *zErrMsg;
};

#endif