#ifndef RESTSQL_H_
# define RESTSQL_H_

# include <cstddef>
# include <iostream>
# include <string>
# include <map>
# include <vector>

# include "itranslatable.h"

# include "create_table.h"
# include "insert.h"
# include "select.h"
# include "update.h"
# include "delete.h"
# include "sqlite.h"

# include "dispatcher.h"

# include "json-forwards.h"
# include "json.h"

#include <fstream>

void	parse_table(std::string &content);
void	parse_row(std::string &content);

void parse_error(Json::Reader &reader);
void printJSONValue(const Json::Value &val);

#endif