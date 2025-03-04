#pragma once

#include <iostream>
#include <sys/types.h>
#include <vector>
#include <map>

#define CHANNEL_PASSWORD_SIZE_LIMIT 50
#define CHANNEL_NAME_SIZE_LIMIT 200


class Channel
{
	private:
		std::string			_Name;
		std::string			_Topic;
		std::vector<id_t>	_User;
		std::vector<id_t>	_Operators;
		std::string			_Password;
	
		bool			invitation_only;
		bool			protected_topic;
		unsigned int	user_limit;
	
	public:
		Channel(std::string	Name, id_t owner);
		~Channel(void);
};
