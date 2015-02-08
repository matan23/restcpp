#ifndef SELECT_H_
# define SELECT_H_

# include "itranslatable.h"
#include <map>

class Select : public ITranslatable
{
private:
	std::string table;
public:
	Select(std::string);
	std::string translateToSqlQuery();
};

#endif