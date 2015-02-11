#include "restsql.h"

using namespace std;

// std::string			method;
//   std::string			uri;
//   std::string			content;
//   std::vector<std::string>	uri_args;

int	post_method(request_t& request_st, tcp::socket& socket) {
	if (request_st.uri_args.size() == 2) {
		request_st.responseBuilder->answer400();
	} else if (request_st.uri_args.size() == 1) {		
		if (request_st.uri_args[0] == "table") {						
			parse_table(request_st, socket);
		} else {
			parse_row(request_st, socket);
		}
	} else {
		request_st.responseBuilder->answer400();
	}
}