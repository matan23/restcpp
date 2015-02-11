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

int		post_method(request_t& request_st, tcp::socket& socket);
int		put_method(request_t& request_st, tcp::socket& socket);
int		delete_method(request_t& request_st, tcp::socket& socket);
int		get_method(request_t& request_st, tcp::socket& socket);
int		patch_method(request_t& request_st, tcp::socket& socket);

void    dispatch(request_t& request_st, tcp::socket& socket);

using boost::asio::ip::tcp;

void	parse_table(request_t& request_st, tcp::socket& socket);
void	parse_row(request_t& request_st, tcp::socket& socket);

void parse_error(Json::Reader &reader);
void printJSONValue(const Json::Value &val);

void		server();
void		client_handler(tcp::socket& socket);

#endif