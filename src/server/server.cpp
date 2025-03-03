#include "server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

server::server(char* port, char* password)
{
	int	rc;

	this->sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->sockfd < 0)
	{
		throw std::runtime_error("error: init socket");
	}

	rc = setsockopt(this->sockfd, IPPROTO_TCP, SO_REUSEADDR | SO_REUSEPORT, NULL, 0);
	if (rc < 0)
	{
		throw std::runtime_error("error: setsockopt() failed");
	}
	struct sockaddr_in6   addr;
	
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family      = AF_INET6;

	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));

	// TODO parse port
	addr.sin6_port = htons(SERVER_PORT);
	rc = bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
	{
		throw std::runtime_error("error: bind() failed");
	}


}

server::~server(void) {}