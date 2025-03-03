#pragma once

#include <iostream>
#include <sys/types.h>

class user
{
	private:
		id_t		_id;
		int			_fd;
		std::string	_name;

	public:
		user(id_t id, int fd, std::string name);
		~user(void);
};