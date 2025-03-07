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

		bool		is_register;
		bool		have_valid_password;

	public:
		User(id_t& new_id, int& new_fd);
		~User(void);

		void	set_id(id_t& new_id);
		void	set_fd(int& new_fd);
		void	set_username(std::string new_username);
		void	set_nickname(std::string& new_nickname);
		void	set_realname(std::string new_realname);
		void	set_is_register(bool& value);
		void	set_have_valid_password(bool& value);

		id_t		get_id() const;
		int			get_fd() const;
		std::string	get_username() const;
		std::string	get_nickname() const;
		std::string	get_realname() const;
		bool		get_is_register(void) const;
		bool		get_have_valid_password(void) const;


		void	do_registration(std::string& new_username, std::string& new_nickname, std::string& new_realname);

};