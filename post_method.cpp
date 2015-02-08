#include "restsql.h"

using namespace std;

void	post_method(std::string &url, std::string &content) {
	cout << url;	
	cout << content;

	// url sould be /table/nameoftable

	if (url.compare("/table") == 0) {
		parse_table(content);
	} else if (url.compare("/person") == 0) {
		parse_row(content);
	} else {
		std::cout << "unsupported";
	}
}