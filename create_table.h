#ifndef CREATE_TABLE_H_
# define CREATE_TABLE_H_

# include "itranslatable.h"
#include <map>

class CreateTable : public ITranslatable
{
private:
	std::string name;
	std::map<std::string, std::string> columns;
public:
	CreateTable(std::string, std::map<std::string, std::string>);
	std::string translateToSqlQuery();
};

#endif