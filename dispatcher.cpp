#include <cstddef>
#include <boost/algorithm/string.hpp>
#include "restsql.h"

using boost::asio::ip::tcp;

t_route gl_routes[] = {
  { (char *)"DELETE", delete_method },
  { (char *)"POST", post_method },
  { (char *)"GET", get_method },
  { (char *)"PUT",  put_method },
  { (char *)"PATCH", patch_method },
  { NULL, NULL }
};

void    dispatch(request_t& request_st, tcp::socket& socket) {
  t_route*  routes = gl_routes;
  std::string method = boost::to_upper_copy(request_st.method);


  for (int i = 0; routes[i].str != NULL; ++i ) {
    if (method.compare(routes[i].str) == 0) {
      try {
        (routes[i].ptr)(request_st, socket);
        return ;
      }
      catch (std::exception& e) {
        std::string error = e.what();
        error += ", the json provided is probably malformatted json, please check documentation for supported payload";
        request_st.responseBuilder->answer400WithPayload(error);
          std::cerr << "Exception: " << "error parsing method, probably malformatted json" << std::endl;
          return;
      }
    }
  }
  request_st.responseBuilder->answer405();
}
