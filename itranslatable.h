#ifndef ITranslatable_H_
# define ITranslatable_H_

# include <string>
class ITranslatable {
	public:
		virtual std::string translateToSqlQuery() = 0;
};

#endif 