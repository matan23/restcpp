#include "response.h"


using boost::asio::ip::tcp;

Response::Response(tcp::socket& socket) : _socket(socket) {
	
}

// ok

void	Response::answer200() {
	std::string message = "HTTP1/1 200 Ok\r\n\r\n";
  	this->sendToClient(message);
}
void	Response::answer200WithPayload(std::string &payload) {
	std::string message = "HTTP1/1 200 Ok\r\n\r\n";
	message += payload;
  	this->sendToClient(message);
}

void	Response::answer201(std::string& location) {
	std::string message = "HTTP1/1 201 Created\r\nLocation ";
  	message += location;
  	message += "\r\n\r\n";
  	this->sendToClient(message);
}

void	Response::answer204() {
	std::string message = "HTTP1/1 204 No Content\r\n\r\n";
	this->sendToClient(message);
}

// bad request

void	Response::answer400() {
	std::string message = "HTTP1/1 400 Bad Request\r\n\r\n";
	this->sendToClient(message);
}

void	Response::answer404() {
	std::string message = "HTTP1/1 404 Not Found\r\n\r\n";
	this->sendToClient(message);
}

void	Response::answer405() {
	std::string message = "HTTP1/1 405 Method Not Allowed\r\n\r\n";
	this->sendToClient(message);
}

// error

void	Response::answer500() {
	std::string message = "HTTP1/1 500 Internal Server Error\r\n\r\n";
	this->sendToClient(message);
}

void	Response::answer501() {
	std::string message = "HTTP1/1 501 Not Implemented\r\n\r\n";
	this->sendToClient(message);
}

// private
void 	Response::sendToClient(std::string &message) {
	boost::system::error_code ignored_error;
  	boost::asio::write(_socket, boost::asio::buffer(message), ignored_error);
}