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
		User(id_t id, int fd, std::string name);
		~User(void);
};