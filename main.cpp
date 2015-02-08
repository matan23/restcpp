#include "restsql.h"
#include <map>

using namespace std;

int	main(void) {
	map<string, string> columns;
	columns["name"] = "text";
	columns["age"] = "int";

	ITranslatable *query = new CreateTable("person", columns);

	cout << query->translateToSqlQuery() << "\n";
}