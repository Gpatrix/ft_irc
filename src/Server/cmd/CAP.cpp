#include "Server.hpp"

void Server::CAP(t_parser_data& data, User*& user)
{
    if (data.cmd.size() < 2)
    {
        logError("CAP requires at least a subcommand\n");
        return;
    }

    std::string subcommand = data.cmd[1];

    if (subcommand == "LS")
    {
        std::string cap_list = "multi-prefix sasl";
        std::string response = ":server CAP " + user->get_nickname() + " LS :" + cap_list + "\r\n";
        send(user->get_fd(), response.c_str(), response.size(), 0);
    }
    else if (subcommand == "REQ")
    {
        if (data.cmd.size() < 3)
        {
           logError("CAP REQ requires a capability list\n");
            return;
        }
        std::string requested_caps = data.cmd[2];
        std::string response = ":server CAP " + user->get_nickname() + " ACK :" + requested_caps + "\r\n";
        send(user->get_fd(), response.c_str(), response.size(), 0);
    }
    else if (subcommand == "END")
        log("CAP negotiation ended for " + user->get_nickname() + "\n");
    else
       logError("ERROR: Unknown CAP subcommand: " + subcommand + "\n");
}
