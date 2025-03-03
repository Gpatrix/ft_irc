#include "server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

server::server(char* port, char* password): password(password)
{
	int	rc;
	int new_sd = -1;
	pollfd	fds[200];
	short	nfds = 1;

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

	fds[0].fd = this->sockfd;
	fds[0].events = POLLIN;
	fds[0].revents = 0;

	while (1)
	{

		rc = poll(fds, nfds, -1);
	
	
		if (rc < 0)
		{
			perror("poll() failed");
			exit(0); // TODO a changer
		}

		std::cout << rc << " internet\n";

		for (short index; index < nfds; index++)
		{
			if (fds[index].revents == 0)
			{
				std::cout << "continue";
				continue ;
			}

			if (fds[index].fd == this->sockfd)
			{
				std::cout << "Listening socket is readable\n";

				do
				{
					/*****************************************************/
					/* Accept each incoming connection. If               */
					/* accept fails with EWOULDBLOCK, then we            */
					/* have accepted all of them. Any other              */
					/* failure on accept will cause us to end the        */
					/* server.                                           */
					/*****************************************************/
					// a optie
					new_sd = accept(this->sockfd, NULL, NULL);
					if (new_sd < 0)
					{
						std::cout << "accept failed\n";
						break;
					}

					/*****************************************************/
					/* Add the new incoming connection to the            */
					/* pollfd structure                                  */
					/*****************************************************/
					printf("  New incoming connection - %d\n", new_sd);

					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
					
					/*****************************************************/
					/* Loop back up and accept another incoming          */
					/* connection                                        */
					/*****************************************************/
				} while (new_sd != -1);
			}
		}
	}
	

}

server::~server(void) {}