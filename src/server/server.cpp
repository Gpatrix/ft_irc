#include "server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

void	server::init_socket(char* &port)
{
	int		rc;

	this->sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->sockfd < 0)
		throw std::runtime_error("Error: init socket");

	int on = 0;
	rc = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (rc < 0)
	{
		throw std::runtime_error("Error: setsockopt() failed");
	}
	

	struct sockaddr_in6	addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));

	char*	end;
	long	port_nb = strtol(port, &end, 10);
	if (*end != '\0' || port_nb < 0)
		throw std::runtime_error("Error: bad port");

	addr.sin6_port = htons(static_cast<uint16_t>(port_nb));
	rc = bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
		throw std::runtime_error("Error: bind() failed");

	rc = listen(this->sockfd, 1024);
	if (rc < 0)
		throw std::runtime_error("Error: listen() failed");

	this->fds[0].fd = this->sockfd;
	this->fds[0].events = POLLIN;
	this->fds[0].revents = 0;
}

void sigint_handler(int)
{
	std::cout << '\n' << "closing server" << '\n';
}

server::server(void): nfds(1) {}

void server::init(char* port, char* password)
{
	int		rc;
	int		new_sd = -1;
	bool	close_conn = false;
	bool	compress_array = false;

	this->password = password;
	this->sockfd = -1;

	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	init_socket(port);

	std::cout <<"server ready\n";
}

void server::run(void)
{
	int		rc;
	bool	compress_array = false;

	while (true)
	{
		rc = poll(this->fds, this->nfds, -1);
		if (rc < 0)
		{
			if (errno != EINTR)
			{
				perror("poll() failed");
			}
			break;
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
}

inline void	server::accept_new_user(void)
{
	static int	new_sd = -1;

	std::cout << "reading server socket\n";
	do
	{
		new_sd = accept(this->sockfd, NULL, NULL);
		if (new_sd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("\taccept() failed");
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
	static std::string	data;
	static char			buffer[500];
	static bool			close_conn = false;
	static int			rc;


	std::cout << "Reading descriptor "<< this->fds[index].fd << '\n';

	data.clear();
	while (true)
	{
		rc = recv(this->fds[index].fd, buffer, sizeof(buffer), 0);
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("\trecv() failed");
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

		data.insert(data.end(), buffer, buffer + rc);

		if (rc < static_cast<int>(sizeof(buffer)))
		{
			std::cout << this->fds[index].fd << ": " << data.c_str() << '\n';
			break;
		}
	}

	if (close_conn)
	{
		close(this->fds[index].fd);
		this->fds[index].fd = -1;

		close_conn = false;

		compress_array = true;
	}
}

server::~server(void)
{
	if (this->sockfd > -1)
		close(this->sockfd);
	
	for (short index = 1; index < this->nfds; index++)
	{
		close(this->fds[index].fd);
	}
}