#ifndef DELETE_H_
# define DELETE_H_

# include "itranslatable.h"
#include <map>

class Delete : public ITranslatable
{
private:
	std::string table;
	int id;
public:
	Delete(std::string, int);
	std::string translateToSqlQuery();
};

#endif