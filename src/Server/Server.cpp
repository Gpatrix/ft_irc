#include "Server.hpp"

// https://www.ibm.com/docs/fr/i/7.5?topic=designs-using-poll-instead-select
// https://tala-informatique.fr/index.php?title=C_socket

void	Server::init_socket(char* &port)
{
	int		rc;

	this->Sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (this->Sockfd < 0)
		throw std::runtime_error("Error: init socket");

	int on = 1;
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
				perror("poll() failed");
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
	static std::vector<pollfd>::iterator it_fd;
	static std::vector<User *>::iterator it_User;
	static std::vector<std::string>::iterator it_string;
	
	it_fd = this->fds.begin() + 1;
	it_User = this->Users.begin();
	it_string = this->data_buffer.begin();

	while (it_User != this->Users.end())
	{
		if ((*it_fd).fd == -1)
		{
			this->fds.erase(it_fd);
			delete *it_User;
			this->Users.erase(it_User);
			this->data_buffer.erase(it_string);
		}

		if (it_User == this->Users.end())
			break;

		it_fd++;
		it_User++;
		it_string++;
	}
}

inline void	Server::accept_new_user(void)
{
	static pollfd	new_User_pollfd;
	static User*	new_User;
	static int	new_fd = -1;

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

		std::cout << "New incoming connection - "<< new_fd << '\n';

		new_User_pollfd.fd = new_fd;
		new_User_pollfd.events = POLLIN;

		new_User = new User(this->Users_id, new_fd);
		this->Users_id++;

		this->Users.push_back(new_User);
		this->fds.push_back(new_User_pollfd);
		this->data_buffer.push_back(std::string(""));
	}
}

inline void	Server::recv_data(short& index, bool& need_compress_fds)
{
	static char			buffer[500];
	static bool			close_conn = false;
	static int			rc;


	this->data_buffer[index - 1].clear();
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
			std::cout << "\tConnection closed - " << this->fds[index].fd << '\n';
			close_conn = true;
			break;
		}

		this->data_buffer[index - 1].insert(this->data_buffer[index - 1].end(), buffer, buffer + rc);

		if (rc < static_cast<int>(sizeof(buffer)))
		{
			std::cout << this->fds[index].fd << ": " << this->data_buffer[index - 1].c_str() << '\n';
			try
			{
				parser(this->data_buffer[index - 1], this->Users[index - 1]);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
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

void Server::sendToAll(Channel &channel, const std::string &message)
{
	const std::vector<id_t> &users = channel.getUser();

	for (size_t i = 0; i < users.size(); i++)
		send(this->Users[users[i]]->get_fd(), message.c_str(), message.length(), 0);
}

Server::~Server(void)
{
	size_t	size;
	size_t	index = 0;

	if (this->Sockfd > -1)
	{
		close(this->Sockfd);
	}
	
	size = this->Users.size();
	
	while (index < size)
	{
		delete this->Users[index];
		close(this->fds[index + 1].fd);
		index++;
	}
	for (std::map<std::string, Channel*>::iterator it = Channels.begin(); it != Channels.end(); ++it)
		delete it->second;
}