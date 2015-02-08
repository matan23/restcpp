#include "restsql.h"

using namespace std;

void	post_method(std::string &url, std::string &content) {

	if (url.compare("/table") == 0) {
		parse_table(content);
	} else {
		std::cout << "unsupported";
	}
}