#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Tests
#include <boost/test/unit_test.hpp>

#include "restsql.h"
 
using namespace std;

std::string create_table_url = "/table";
	std::string content = "whatever";


BOOST_AUTO_TEST_CASE(createTable)
{
	
	int res = post_method(create_table_url, content);

    BOOST_CHECK(res == 1);
}

// BOOST_AUTO_TEST_CASE(createRow)
// {
// 	std::string create_row_url = "/person";
// 	std::string content = "whateever";

//  	BOOST_CHECK(post_method(create_row_url, content) == 2);
// }

// BOOST_AUTO_TEST_CASE(unsupported)
// {
// 	std::string unsupported_url = "/person";
// 	std::string content = "whateever";

//  	BOOST_CHECK(post_method(unsupported_url, content) == -1);
// }