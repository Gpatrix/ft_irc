#include "server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

void	server::init_socket(char* &port)
{
	int		rc;

	this->sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->sockfd < 0)
		throw std::runtime_error("error: init socket");

	int on = 0;
	rc = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
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

	this->fds[0].fd = this->sockfd;
	this->fds[0].events = POLLIN;
	this->fds[0].revents = 0;
	this->nfds = 1;
}


server::server(char* port, char* password): password(password)
{
	int		rc;
	int		new_sd = -1;
	char	buffer[80];
	bool	close_conn = false;
	bool	compress_array = false;

	init_socket(port);

	std::cout << "server ready\n";
	while (1)
	{

		rc = poll(this->fds, nfds, -1);
		if (rc < 0)
		{
			perror("poll() failed");
			exit(0); // TODO a changer
		}

		int current_size = nfds;
		for (short index = 0; index < current_size; index++)
		{
			if (this->fds[index].revents == 0)
				continue ;

			if (this->fds[index].fd == this->sockfd)
			{
				std::cout << "reading server socket\n";

				do
				{
					// a optie
					new_sd = accept(this->sockfd, NULL, NULL);
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  accept() failed");
							// end_server = true;
						}
						break;
					}

					std::cout << "\tNew incoming connection - "<< new_sd << '\n';

					this->fds[nfds].fd = new_sd;
					this->fds[nfds].events = POLLIN;
					nfds++;
					
				} while (new_sd != -1);
			}
			else
			{
				std::cout << "reading  Descriptor "<< this->fds[index].fd << '\n';
				close_conn = false;
				while (true)
				{
					rc = recv(this->fds[index].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  recv() failed");
							close_conn = true;
						}
						break;
					}

					if (rc == 0)
					{
						std::cout << "\tConnection closed\n";
						close_conn = true;
						break;
					}

					std::cout << '\t' << rc << " bytes received\n";

					rc = send(this->fds[index].fd, buffer, rc, 0);
					if (rc < 0)
					{
						perror("  send() failed");
						close_conn = true;
						break;
					}
					if (rc < static_cast<int>(sizeof(buffer)))
					{
						break;
					}

				}

				if (close_conn)
				{
					close(this->fds[index].fd);
					this->fds[index].fd = -1;
					compress_array = true;
				}
			}

			if (compress_array)
			{
				compress_array = false;
				for (int i = 0; i < nfds; i++)
				{
					if (this->fds[i].fd == -1)
					{
						for(int j = i; j < nfds-1; j++)
						{
							this->fds[j].fd = this->fds[j+1].fd;
						}
						i--;
						nfds--;
					}
				}
			}
			}
	}
}

server::~server(void)
{
	for (short index = 0; index < this->nfds; index++)
	{
		close(this->fds[index].fd);
	}
}