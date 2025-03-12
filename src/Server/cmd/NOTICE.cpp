#include "Server.hpp"

// https://modern.ircdocs.horse/#notice-message
void Server::NOTICE(t_parser_data& data, User*& user)
{
    if (data.cmd.size() < 3)
    {
        std::clog << "ERROR: NOTICE requires at least a target and a message\n";
        return;
    }

    std::vector<std::string> targets = split(data.cmd[1], ',');
    std::string message = data.cmd[2];

    if (message.empty())
    {
        std::clog << "ERROR: NOTICE message is empty\n";
        return;
    }

    for (size_t i = 0; i < targets.size(); ++i)
    {
        std::string& target = targets[i];

        if (!target.empty() && target[0] == '#')
        {
            std::map<std::string, Channel*>::iterator it = this->Channels.find(target);
            if (it != this->Channels.end())
            {
				sendToAll(it->second->getUser(),":" + user->get_nickname() + " NOTICE " + target + " :" + message + "\r\n");
            }
        }
        else
        {
            User* target_user = find_User(target);
            if (target_user != NULL)
            {
                std::string notice_msg = ":" + user->get_nickname() + " NOTICE " + target + " :" + message + "\r\n";
                send(target_user->get_fd(), notice_msg.c_str(), notice_msg.size(), 0);
            }
        }
    }
}

