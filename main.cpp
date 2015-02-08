#include "restsql.h"

using namespace std;

int	main(void) {

	ITranslatable *query = new CreateTable();
	cout << query->translateToSqlQuery();
}