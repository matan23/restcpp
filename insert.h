#ifndef INSERT_H_
# define INSERT_H_

# include "itranslatable.h"
#include <map>

class Insert : public ITranslatable
{
private:
	std::string table;
	std::map<std::string, std::string> values;
public:
	Insert(std::string, std::map<std::string, std::string>);
	std::string translateToSqlQuery();
};

#endif