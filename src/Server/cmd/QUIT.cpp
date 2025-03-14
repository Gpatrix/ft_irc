#include "Server.hpp"

// https://modern.ircdocs.horse/#quit-message
void	Server::QUIT(t_parser_data& data, User* &user)
{
	std::string msg = (data.cmd.size() == 1) ? "" : data.cmd[1];
	std::string quit_msg = ":" + user->get_nickname() + " QUIT :" + msg + "\r\n";

	for (std::vector<User*>::iterator it = this->Users.begin(); it != this->Users.end(); ++it)
		send((*it)->get_fd(), quit_msg.c_str(), quit_msg.length(), 0);

	this->close_connection(user->get_fd());
	this->ERROR("QUIT", user->get_fd());
}

void	Server::close_connection(const int& fd)
{
	close(fd);
	this->need_compress_fds = true;
	for (size_t index = 0; index < this->fds.size(); index++)
	{
		if (this->fds[index].fd == fd)
		{
			this->fds[index].fd = -1;
			return;
		}
	}
}

void	Server::compress_fds(void)
{
	static std::vector<pollfd>::iterator		it_fd;
	static std::vector<User *>::iterator		it_User;
	static std::vector<std::string>::iterator	it_string;
	static std::map<std::string, Channel*>::iterator it_Channels;
	static size_t	channel_index;

	
	it_fd = this->fds.begin() + 1;
	it_User = this->Users.begin();
	it_string = this->data_buffer.begin();

	while (it_User != this->Users.end())
	{
		if ((*it_fd).fd == -1)
		{
			it_Channels = this->Channels.begin();
			channel_index = 0;
			for (; it_Channels != this->Channels.end(); it_Channels++)
			{
				channel_index++;
				(*it_Channels).second->removeOperator((*it_User)->get_id());
				(*it_Channels).second->removeUser((*it_User)->get_id());
				if ((*it_Channels).second->getUsers().size() == 0)
				{
					delete (*it_Channels).second;
					this->Channels.erase(it_Channels);
					if (channel_index >= this->Channels.size())
						break;
				}
			}
			this->fds.erase(it_fd);
			delete *it_User;
			this->Users.erase(it_User);
			this->data_buffer.erase(it_string);
			continue;
		}

		it_fd++;
		it_User++;
		it_string++;
	}
}

void	Server::ERROR(std::string msg, const int& fd) const
{
	msg = ":" SERVER_NAME " ERROR " + msg + "\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
}