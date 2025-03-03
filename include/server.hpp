#pragma once

#include "user.hpp"
#include "channel.hpp"
#include <iostream>
#include <vector>
#include <map>


class server
{
	private:
		std::map<std::string&, channel&>	channels;
		std::vector<user*>					user;
		std::string							password;

	public:
		server(void);
		~server(void);
};
