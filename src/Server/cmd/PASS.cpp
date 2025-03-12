#include "Server.hpp"

// https://dd.ircdocs.horse/refs/commands/pass
void	Server::PASS(t_parser_data& data, User* &user)
{
	if (data.cmd.size() != 2)
	{
		Numerics::_461_ERR_NEEDMOREPARAMS(data.cmd[0], user->get_fd());
		return;
	}
	
	const std::string& providedPassword = data.cmd[1];
	bool isValid = (this->Password == providedPassword);
	user->set_have_valid_password(isValid);

	if (!isValid)
		Numerics::_464_ERR_PASSWDMISMATCH(user->get_fd());
}
