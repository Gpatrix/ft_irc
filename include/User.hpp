#pragma once

#include <iostream>
#include <sys/types.h>

class User
{
	private:
		id_t		_id;
		int			_fd;
		std::string	_name;

	public:
		User(id_t& new_id, int& new_fd);
		~User(void);

		void	set_id(id_t& new_id);
		void	set_fd(int& new_fd);
		void	set_name(std::string& new_name);
};