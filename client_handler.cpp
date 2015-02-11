#include "restsql.h"


using boost::asio::ip::tcp;
using namespace std;
// debug : display all boost::smatch's results
// for (unsigned int i=0; i < result.size(); i++) {
//   std::cout << "RESULT " << i << " >>" << result[i] << "<<" << std::endl;
// }

void	get_request_from_socket(tcp::socket &socket, std::string &request) {
  boost::array<char, BUFFER_SIZE> buffer;
  int size;

  size = socket.read_some(boost::asio::buffer(buffer));
  std::copy(buffer.begin(), buffer.begin() + size, std::back_inserter(request));
}

bool	parse_request_string(const std::string& str, request_t& request_st) {
  boost::regex	pattern_method_uri("^([A-Za-z]+)[ \t]+([\\S]+)");
  boost::regex	pattern_content("^([^\r\n]+\r\n)*\r\n(.*)$");
  boost::smatch	result;
  std::string uri_copy;
  std::string delimiter = "/";
  int pos = 0;
  std::string token;

  if ( ! boost::regex_search(str, result, pattern_method_uri) )
    return (false);
  request_st.method = result[1];
  request_st.uri = result[2];


  if ( boost::regex_search(str, result, pattern_content) )
    request_st.content = result[ result.size() - 1 ];

  uri_copy = request_st.uri;
  while ((pos = uri_copy.find(delimiter)) != (int)std::string::npos) {
    token = uri_copy.substr(0, pos);
    if ( token.length() != 0 )
      request_st.uri_args.push_back(token);
    uri_copy.erase( 0, pos + delimiter.length() );
  }
  if (uri_copy.length() != 0)
    request_st.uri_args.push_back(uri_copy);
  return (true);
}

void	client_handler(tcp::socket& socket) {
  std::string	request;
  request_t	request_st;

  get_request_from_socket(socket, request);
  if (parse_request_string(request, request_st) == false)
    return ;
  request_st.responseBuilder = new Response(socket);
  dispatch(request_st, socket);
  socket.close();
}
