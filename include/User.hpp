#pragma once

#include <iostream>
#include <sys/types.h>

class User
{
	private:
		id_t		_id;
		int			_fd;
		std::string	_username;
		std::string	_nickname;
		std::string	_realname;

		bool is_register;

	public:
		User(id_t& new_id, int& new_fd);
		~User(void);

		void	set_id(id_t& new_id);
		void	set_fd(int& new_fd);

		void	set_username(std::string& new_username);
		void	set_nickname(std::string& new_nickname);
		void	set_realname(std::string& new_realname);

		void	do_registration(std::string& new_username, std::string& new_nickname, std::string& new_realname);

};