#include "restsql.h"

using namespace std;

int	patch_method(request_t& request_st, ATTR_UNUSED tcp::socket& socket) {
	request_st.responseBuilder->answer405();
	return 0;
}