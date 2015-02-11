#include "response.h"


using boost::asio::ip::tcp;

Response::Response(tcp::socket& socket) : _socket(socket) {
	_defaultHeader = "\nContent-Type: application/json\nConnection: close\r\n\r\n";
}

// ok

void	Response::answer200() {
	std::string message = "HTTP1/1 200 Ok\nConnection: close\r\n\r\n";
  	this->sendToClient(message);
}
void	Response::answer200WithPayload(std::string &payload) {
	std::string message = "HTTP1/1 200 Ok\nConnection: close\r\n\r\n";
	message += payload;
  	this->sendToClient(message);
}

// put the url with the id in the post method
void	Response::answer201(std::string& location) {
	std::string message = "HTTP1/1 201 Created\nLocation: " + location + "\nConnection: close\r\n\r\n";
  	this->sendToClient(message);
  	std::cout << message << std::endl;
}

void	Response::answer204() {
	std::string message = "HTTP1/1 204 No Content\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

// bad request

void	Response::answer400WithPayload(std::string &payload) {
	Json::Value response;	
	response["error"] = payload;

	Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	std::string error = writer.write(response);

	std::string message = "HTTP1/1 400 Bad Request" + _defaultHeader + error;
	this->sendToClient(message);
}


void	Response::answer400() {
	std::string message = "HTTP1/1 400 Bad Request\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

void	Response::answer403(std::string &payload) {
	Json::Value response;	
	response["error"] = payload;

	Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	std::string error = writer.write(response);

	std::string message = "HTTP1/1 403 Bad Request" + _defaultHeader + error;
	this->sendToClient(message);
}

void	Response::answer404() {
	std::string message = "HTTP1/1 404 Not Found\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

void	Response::answer405() {
	std::string message = "HTTP1/1 405 Method Not Allowed\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

// error

void	Response::answer500() {
	std::string message = "HTTP1/1 500 Internal Server Error\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

void	Response::answer501() {
	std::string message = "HTTP1/1 501 Not Implemented\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

// private
void 	Response::sendToClient(std::string &message) {
	boost::system::error_code ignored_error;
  	boost::asio::write(_socket, boost::asio::buffer(message), ignored_error);
}