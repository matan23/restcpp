#include "restsql.h"

using namespace std;

// std::string			method;
//   std::string			uri;
//   std::string			content;
//   std::vector<std::string>	uri_args;

int	post_method(request_t& request_st, tcp::socket& socket) {
	
	cout << request_st.method;
	cout << request_st.uri;
	cout << request_st.content;
// ...
	if (request_st.uri_args.size() == 2) {
		cout << "ERROR BAD URL" << endl;
	} else if (request_st.uri_args.size() == 1) {
		cout << "looks ok" << endl;
		cout << request_st.uri_args[0] << endl;
		if (request_st.uri_args[0] == "table") {						
			cout << "parsing table" << endl;
			parse_table(request_st, socket);
		} else {
			cout << "trying to parse row" << endl;
			parse_row(request_st.content);
		}
	} else {
		cout << "ERROR BAD URL" << endl;
	}



for( std::vector<std::string>::const_iterator i = request_st.uri_args.begin(); i != request_st.uri_args.end(); ++i)
    std::cout << *i << endl;
}