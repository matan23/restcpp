#include "restsql.h"

using boost::asio::ip::tcp;

#ifndef RESPONSE_H_
# define RESPONSE_H_


static std::string _payload = "";

class Response {
	private:
		tcp::socket& 		_socket;

		void	sendToClient(std::string &message);

	public:
		Response(tcp::socket& socket);

		void	answer200();
		void	answer200WithPayload(std::string &payload = _payload);
		void	answer201(std::string& location);
		void	answer204();

		void	answer400();
		void	answer404();
		void	answer405();
		void	answer500();
		void	answer501();
};

#endif