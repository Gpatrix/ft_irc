#include "Numerics.hpp"

void Numerics::_353_RPL_NAMREPLY(const std::string& client, const std::string& symbol, const std::string& channel, const std::vector<std::string>& users, const int& fd)
{
	// Construction de la liste des utilisateurs sous forme d'une seule chaîne
	std::string userList;
	for (size_t i = 0; i < users.size(); i++)
	{
		userList += users[i];
		if (i < users.size() - 1)
			userList += " ";
	}
	std::string msg = ":" SERVER_NAME " 353 " + client + " " + symbol + " " + channel + " :" + userList + "\r\n";
	send(fd, msg.c_str(), msg.size(), 0);
	log(msg);
}
