#include "User.hpp"

User::User(id_t& new_id, int& new_fd): _id(new_id), _fd(new_fd) {}

void	User::set_id(id_t& new_id)
{
	this->_id = new_id;
}

void	User::set_fd(int& new_fd)
{
	this->_fd = new_fd;
}

void	User::set_name(std::string& new_name)
{
	this->_name = new_name;
}


// TODO fermer proprement la connection
User::~User(void) {}
