#include <iostream>
#include <vector>

#define PASSWORD_SIZE_LIMIT 50

class channel
{
private:
	std::vector<id_t>	user;
	std::vector<id_t>	operators;
	std::string			password;
 
	bool			invitation_only;
	bool			protected_topic;
	unsigned int	user_limit;
};