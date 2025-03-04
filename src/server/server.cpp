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

inline void	server::accept_new_user(void)
{
	static int	new_sd = -1;

	std::cout << "reading server socket\n";
	do
	{
		// TODO a optie
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

		this->fds[this->nfds].fd = new_sd;
		this->fds[this->nfds].events = POLLIN;
		this->nfds++;
	} while (new_sd != -1);
}

inline void	server::recv_data(short& index, bool& compress_array)
{
	static char	buffer[500];
	static bool	close_conn = false;
	static int		rc;


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

volatile bool got_sigint = 0;

void sigint_handler(int signal) {
    got_sigint = 1;  // Set flag when SIGINT is received
	std::cout << "asd\n";
}

server::server(char* port, char* password): password(password)
{
	int		rc;
	int		new_sd = -1;
	bool	close_conn = false;
	bool	compress_array = false;

	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	sigset_t mask;
	sigemptyset(&mask);
	// sigaddset(&mask, SIGINT);  // Block SIGINT while polling

	init_socket(port);

	std::cout <<"server ready\n";
	while (!got_sigint)
	{
		// rc = poll(this->fds, this->nfds, -1);
		rc = ppoll(this->fds, this->nfds, NULL, &mask);
		if (rc < 0)
		{
			perror("poll() failed");
			exit(0); // TODO a changer
		}

		if (rc == 0)
		{
			break;
		}
		

		int current_size = this->nfds;
		for (short index = 0; index < current_size; index++)
		{
			if (this->fds[index].revents == 0)
				continue ;

			if (this->fds[index].fd == this->sockfd)
			{
				this->accept_new_user();
			}
			else
			{
				recv_data(index, compress_array);
			}
		}
		if (compress_array)
			{
				compress_array = false;
				for (int i = 0; i < this->nfds; i++)
				{
					if (this->fds[i].fd == -1)
					{
						for(int j = i; j < this->nfds-1; j++)
						{
							this->fds[j].fd = this->fds[j+1].fd;
						}
						i--;
						this->nfds--;
					}
				}
			}
	}
	std::cout << "closing server" << '\n';
}

server::~server(void)
{
	for (short index = 0; index < this->nfds; index++)
	{
		close(this->fds[index].fd);
	}
}