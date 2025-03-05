#include "Server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

void	Server::init_socket(char* &port)
{
	int		rc;

	this->Sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->Sockfd < 0)
		throw std::runtime_error("Error: init socket");

	int on = 0;
	rc = setsockopt(this->Sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
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
	rc = bind(this->Sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
		throw std::runtime_error("Error: bind() failed");

	rc = listen(this->Sockfd, 1024);
	if (rc < 0)
		throw std::runtime_error("Error: listen() failed");

	pollfd	sockfd;

	sockfd.fd = this->Sockfd;
	sockfd.events = POLLIN;
	sockfd.revents = 0;

	this->fds.push_back(sockfd);
}

void sigint_handler(int)
{
	std::cout << '\n' << "closing Server" << '\n';
}

Server::Server(void): Users_id(0) {}

void Server::init(char* port, char* password)
{
	int		rc;
	int		new_sd = -1;
	bool	close_conn = false;
	bool	need_compress_fds = false;

	this->Password = password;
	this->Sockfd = -1;

	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	init_socket(port);

	std::cout <<"Server ready\n";
}

void Server::run(void)
{
	int		rc;
	bool	need_compress_fds = false;

	while (true)
	{
		rc = poll(this->fds.data(), this->fds.size(), -1);
		if (rc < 0)
		{
			if (errno != EINTR)
			{
				perror("poll() failed");
			}
			break;
		}

		if (rc == 0)
			break;

		int current_size = static_cast<int>(this->fds.size());
		for (short index = 0; index < current_size; index++)
		{
			if (this->fds[index].revents == 0)
				continue ;

			if (this->fds[index].fd == this->Sockfd)
				this->accept_new_user();
			else
				recv_data(index, need_compress_fds);
		}
		if (need_compress_fds)
		{
			need_compress_fds = false;
			
			compress_fds();
		}
	}
}

inline void	Server::compress_fds(void)
{
	std::vector<pollfd>::iterator it = this->fds.begin();
	while (it != this->fds.end())
	{
		if ((*it).fd == -1)
		{
			this->fds.erase(it);
		}

		if (it == this->fds.end())
		{
			break;
		}

		it++;
	}
}


inline void	Server::accept_new_user(void)
{
	static pollfd	new_user_pollfd;
	static int	new_fd = -1;

	std::cout << "reading Server socket\n";
	while (true)
	{
		new_fd = accept(this->Sockfd, NULL, NULL);
		if (new_fd < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("\taccept() failed");
			}
			break;
		}

		std::cout << "\tNew incoming connection - "<< new_fd << '\n';

		new_user_pollfd.fd = new_fd;
		new_user_pollfd.events = POLLIN;

		this->fds.push_back(new_user_pollfd);
	}
}

inline void	Server::recv_data(short& index, bool& need_compress_fds)
{
	static std::string	data;
	static char			buffer[500];// TODO metre limit de bits
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

		need_compress_fds = true;
	}
}

Server::~Server(void)
{
	if (this->Sockfd > -1)
		close(this->Sockfd);
	
	if (this->fds.size() > 1)
	{
		for (std::vector<pollfd>::iterator it = this->fds.begin() + 1;
		it != this->fds.end(); it++)
		{
			close((*it).fd);
		}
	}
}