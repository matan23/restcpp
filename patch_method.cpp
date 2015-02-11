#include "restsql.h"

using namespace std;

int	patch_method(request_t& request_st, __attribute__((unused))tcp::socket& socket) {
	request_st.responseBuilder->answer405();
	return 0;
}