#include "restsql.h"

using namespace std;

int	main(void) {
	map<string, string> columns;
	columns["name"] = "text";
	columns["age"] = "int";

	ITranslatable *create_table = new CreateTable("person", columns);

	cout << create_table->translateToSqlQuery() << "\n";

	map<string, string> values;
	values["name"] = "Jero";
	values["age"] = "24";

	ITranslatable *insert = new Insert("person", values);

	cout << insert->translateToSqlQuery() << "\n";
}