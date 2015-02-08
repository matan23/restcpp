#ifndef CREATE_TABLE
# define CREATE_TABLE

# include "itranslatable.h"

class CreateTable : public ITranslatable
{
public:
	std::string translateToSqlQuery();
};

#endif