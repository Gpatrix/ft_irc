#include "User.hpp"

User::User(id_t& new_id, int& new_fd)
: _id(new_id), _fd(new_fd), is_register(false), have_valid_password(false)
 , is_invisible(false) {}

void	User::set_id(id_t& new_id)
{
	this->_id = new_id;
}

void	User::set_fd(int& new_fd)
{
	this->_fd = new_fd;
}

void	User::set_username(const std::string& new_username)
{
	this->_username = new_username;
}

void	User::set_nickname(const std::string& new_nickname)
{
	this->_nickname = new_nickname;
}

void	User::set_realname(const std::string& new_realname)
{
	this->_realname = new_realname;
}

void	User::set_is_register(bool value)
{
	this->is_register = value;
}

void	User::set_is_invisible(bool value)
{
	this->is_invisible = value;
}

void	User::set_have_valid_password(bool value)
{
	this->have_valid_password = value;
}

id_t		User::get_id() const
{
	return (this->_id);
}

int			User::get_fd() const
{
	return (this->_fd);
}

std::string	User::get_username() const
{
	return (this->_username);
}

std::string	User::get_nickname() const
{
	return (this->_nickname);
}

std::string	User::get_realname() const
{
	return (this->_realname);
}

bool		User::get_is_register(void) const
{
	return (this->is_register);
}

bool		User::get_is_invisible(void) const
{
	return (this->is_invisible);
}

bool		User::get_have_valid_password(void) const
{
	return (this->have_valid_password);
}

User::~User(void) {}
