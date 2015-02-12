#ifndef RESTSQL_H_
# define RESTSQL_H_

# include <cstddef>
# include <fstream>
# include <iostream>
# include <boost/array.hpp>
# include <string>
# include <map>
# include <vector>
# include <boost/bind.hpp>
# include <boost/asio.hpp>
# include <boost/regex.hpp>


# include "itranslatable.h"

# include "create_table.h"
# include "insert.h"
# include "select.h"
# include "update.h"
# include "delete.h"
# include "sqlite.h"

# include "json-forwards.h"
# include "json.h"


# include "response.h"

# define BUFFER_SIZE (8192)

using boost::asio::ip::tcp;
using namespace std;

#if (__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#       define ATTR_UNUSED         __attribute__((__unused__))
#else
#       define ATTR_UNUSED
#endif

typedef struct			request_s {
  std::string			method;
  std::string			uri;
  std::string			content;
  std::vector<std::string>	uri_args;
  Response				*responseBuilder;
}						request_t;

typedef	struct	s_route {
  char*		str;
  int		(*ptr)(request_t& request_st, tcp::socket& socket);
}				t_route;

bool isInteger(const std::string & s);

int		post_method(request_t& request_st, tcp::socket& socket);
int		put_method(request_t& request_st, tcp::socket& socket);
int		delete_method(request_t& request_st, tcp::socket& socket);
int		get_method(request_t& request_st, tcp::socket& socket);
int		patch_method(request_t& request_st, tcp::socket& socket);

void    dispatch(request_t& request_st, tcp::socket& socket);

using boost::asio::ip::tcp;

void	parse_table(request_t& request_st, tcp::socket& socket);
void	parse_row(request_t& request_st, tcp::socket& socket);
int     getNumberOfRows(string table, int id);

bool jsonValueIsSuppportedType(Json::Value &value);
bool jsonKeyIsSuppportedType(Json::Value &value);
bool 	jsonIsSuppportedType(Json::ValueIterator &iterator);
std::string parse_error(Json::Reader &reader);
void printJSONValue(const Json::Value &val);

void		server();
void		client_handler(tcp::socket& socket);

#endif
