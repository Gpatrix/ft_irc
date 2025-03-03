#include "server.hpp"

server::server(char* port, char* password)
{
	this->sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->sockfd == 1)
	{
		throw std::runtime_error("error: init socket");
	}

	setsockopt(this->sockfd, IPPROTO_TCP, SO_REUSEADDR | SO_REUSEPORT, const void *optval, socklen_t optlen);
	
}

server::~server(void) {}