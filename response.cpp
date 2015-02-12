#include "response.h"


using boost::asio::ip::tcp;

std::string	payload_status_and_error(string status, string error) {
	Json::Value response;	
	response["error"] = error;
	response["status"] = status;
	
	Json::StyledWriter writer;
	std::string output = writer.write(response);

	return output;
}


Response::Response(tcp::socket& socket) : _socket(socket) {
	_defaultHeader = "\nContent-Type: application/json\nConnection: close\r\n\r\n";
}

// ok

void	Response::answer200() {
	std::string message = "HTTP/1.0 200 Ok" + _defaultHeader + payload_status_and_error("success", "OK");
  	this->sendToClient(message);
}
void	Response::answer200WithPayload(std::string &payload) {
	std::string message = "HTTP/1.0 200 Ok" + _defaultHeader;
	message += payload;
  	this->sendToClient(message);
}

// put the url with the id in the post method
void	Response::answer201(std::string& location) {
	std::string message = "HTTP/1.0 201 Created\nLocation: " + location + _defaultHeader + payload_status_and_error("success", "Created");
  	this->sendToClient(message);
  	std::cout << message << std::endl;
}

void	Response::answer204() {
	std::string message = "HTTP/1.0 204 No Content\nConnection: close\r\n\r\n";
	this->sendToClient(message);
}

// bad request

void	Response::answer400WithPayload(std::string &payload) {
	Json::Value response;	
	response["error"] = payload;

	Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	std::string error = writer.write(response);

	std::string message = "HTTP/1.0 400 Bad Request" + _defaultHeader + payload_status_and_error("Failure", payload);
	this->sendToClient(message);
}


void	Response::answer400() {
	std::string message = "HTTP/1.0 400 Bad Request" + _defaultHeader + payload_status_and_error("Failure", "Bad Request");
	this->sendToClient(message);
}

void	Response::answer403(std::string &payload) {
	Json::Value response;	
	response["error"] = payload;

	Json::StyledWriter writer;
	// Make a new JSON document for the configuration. Preserve original comments.
	std::string error = writer.write(response);

	std::string message = "HTTP/1.0 403 Bad Request" + _defaultHeader + payload_status_and_error("Failure", payload);
	this->sendToClient(message);
}

void	Response::answer404() {
	std::string message = "HTTP/1.0 404 Not Found" + _defaultHeader + payload_status_and_error("Failure", "Not found");
	this->sendToClient(message);
}

void	Response::answer405() {
	std::string message = "HTTP/1.0 405 Method Not Allowed" + _defaultHeader + payload_status_and_error("Failure", "Method Not Allowed");
	this->sendToClient(message);
}

// error

void	Response::answer500() {
	std::string message = "HTTP/1.0 500 Internal Server Error" + _defaultHeader + payload_status_and_error("Failure", "Bad request");
	this->sendToClient(message);
}

void	Response::answer501() {
	std::string message = "HTTP/1.0 501 Not Implemented" + _defaultHeader + payload_status_and_error("Failure", "Bad request");
	this->sendToClient(message);
}

// private
void 	Response::sendToClient(std::string &message) {
	boost::system::error_code ignored_error;
  	boost::asio::write(_socket, boost::asio::buffer(message), ignored_error);
}