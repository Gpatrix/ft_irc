#include "Server.hpp"

std::vector<std::string> Server::ft_split(const std::string &str, char delimiter)
{
	std::vector<std::string> result;
	size_t pos_begin = 0, pos_end = 0;

	while ((pos_end = str.find(delimiter, pos_begin)) != std::string::npos)
	{
		result.push_back(str.substr(pos_begin, pos_end - pos_begin));
		pos_begin = pos_end + 1;
	}
	result.push_back(str.substr(pos_begin));
	return result; 	
}

bool Server::isValidNickname(const std::string &nickname)
{
	if (nickname.empty() || nickname.length() > 30)
		return false;

	if (!std::isalpha(nickname[0]))
		return false;

	for (size_t i = 1; i < nickname.length(); i++)
	{
		if (!std::isalnum(nickname[i]) && nickname[i] != '-' && nickname[i] != '_')
			return false;
	}
	return true;
}

bool Server::isNicknameTaken(const std::string &nickname)
{
	for (size_t i = 0; i < Users.size(); i++)
	{
		if (Users[i]->get_nickname() == nickname)
			return true;
	}
	return false;
}

User*	Server::find_User(const std::string& user_name)
{
	std::vector<User *>::iterator it = this->Users.begin();
	for (; it != this->Users.end(); it++)
	{
		if ((*it)->get_nickname() == user_name)
			return (*it);
	}
	return (NULL);
}

User*	Server::find_User(const id_t& user_id)
{
	std::vector<User *>::iterator it = this->Users.begin();
	for (; it != this->Users.end(); it++)
	{
		if ((*it)->get_id() == user_id)
			return (*it);
	}
	return (NULL);
}