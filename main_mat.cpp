#include "restsql.h"

using namespace std;

int	main(void) {
		string get_method = "GET";
		string post_method = "POST";
		string put_method = "PUT";
		string delete_method = "DELETE";
		string patch_method = "PATCH";
		string url = "/table/mytablename";
		string create_table_content = "{\n    \"name\":\"Person\",\n    \"columns\": {\n        \"name\":\"text\",\n        \"age\":\"int\"\n    }\n}\n";


		// dispatch(patch_method, url, content);
		// dispatch(post_method, url, create_table_content);
		// dispatch(get_method, url, content);
		// dispatch(delete_method, url, content);

		string urlCreateRow = "/person";
		string create_row_content = "{\n    \"name\":\"jero\",\n      \"age\":\"1\"\n}";
		dispatch(post_method, urlCreateRow, create_row_content);
}