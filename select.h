#ifndef SELECT_H_
# define SELECT_H_

# include "itranslatable.h"
#include <map>

class Select : public ITranslatable
{
private:
	std::string table;
	int id;
public:
	Select(std::string);
	Select(std::string, int);
	std::string translateToSqlQuery();
};

#endif