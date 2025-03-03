#include "server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

server::server(char* port, char* password): password(password)
{
	int	rc;

	this->sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->sockfd < 0)
		throw std::runtime_error("error: init socket");




	int buffer = 0;
	rc = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &buffer, sizeof(buffer));
	if (rc < 0)
		throw std::runtime_error("error: setsockopt() failed");
	



	struct sockaddr_in6	addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));

	char*	end;
	long	port_nb = strtol(port, &end, 10);
	if (*end != '\0' || port_nb < 0)
		throw std::runtime_error("bad port");
	
	addr.sin6_port = htons(static_cast<uint16_t>(port_nb));
	rc = bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
		throw std::runtime_error("error: bind() failed");




	rc = listen(this->sockfd, 1024);
	if (rc < 0)
		throw std::runtime_error("error: listen() failed");

	pollfd	host;

	host.fd = this->sockfd;
	host.events = POLLIN;
	host.revents = 0;

	this->pollfds.push_back(host);

	rc = poll(&this->pollfds[0], this->pollfds.size(), -1);

	std::cout << "internet\n";

}

server::~server(void) {}