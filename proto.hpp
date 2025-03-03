#include <iostream>
#include <vector>
#include <map>

#define PASSWORD_SIZE_LIMIT 50

// https://modern.ircdocs.horse/
// https://www.rfc-editor.org/rfc/rfc1459.html

class user
{
	private:
		id_t		id;
		int			fd;
		std::string	name;
};

class channel
{
	private:
		std::string			Name;
		std::string			topic;
		std::vector<id_t>	user;
		std::vector<id_t>	operators;
		std::string			password;
	
		bool			invitation_only;
		bool			protected_topic;
		unsigned int	user_limit;
};

class server
{
	private:
		std::map<std::string&, channel&>	channels;
		std::vector<user&>					user;
};
