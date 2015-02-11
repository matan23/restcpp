#include "restsql.h"

void	server()
{
	boost::asio::io_service io;
	tcp::acceptor	acceptor(io, tcp::endpoint(tcp::v4(), 8080));
	tcp::socket	socket(io);

	try {
		while (1) {
			acceptor.accept(socket);
			client_handler(socket);
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}