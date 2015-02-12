#include "restsql.h"


void	server()
{
	boost::asio::io_service io;
	tcp::acceptor	*acceptor;
	tcp::socket		*socket;

	try {
		acceptor = new tcp::acceptor(io, tcp::endpoint(tcp::v4(), 8080));
		socket = new tcp::socket(io);
	}
	catch (std::exception& e) {
		std::cerr << "a server is already running! You can still restart it with ./launcher.rc restart" << std::endl;
		exit(0);
	}

	try {
		while (1) {
			acceptor->accept(*socket);
			client_handler(*socket);
		}
	}
	catch (std::exception& e) {
		
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}