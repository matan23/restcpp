#include <cstddef>
#include "restsql.h"

// using namespace std;

t_route gl_routes[] = {
  { (char *)"DELETE", delete_method },
  { (char *)"POST", post_method },
  { (char *)"GET", get_method },
  { (char *)"PUT",  put_method },
  { (char *)"PATCH", patch_method },
  { NULL, NULL }
};

void    dispatch(std::string &method, std::string &url, std::string &content) {
  t_route*  routes = gl_routes;

  for (int i = 0; routes[i].str != NULL; ++i ) {
    if (method.compare(routes[i].str) == 0) {
      (routes[i].ptr)(url, content);
      return ;
    }
  }
}
