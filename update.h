#ifndef UPDATE_H_
# define UPDATE_H_

# include "itranslatable.h"
#include <map>

class Update : public ITranslatable
{
private:
	std::string table;
	int id;
	std::map<std::string, std::string> values;
public:
	Update(std::string, int, std::map<std::string, std::string>);
	std::string translateToSqlQuery();
};

#endif