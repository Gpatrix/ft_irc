#include "channel.hpp"

channel::channel(std::string name, id_t owner): _Name(name)
{
	this->_Operators.push_back(owner);
	this->_User.push_back(owner);
}

// TODO voir ci besoi d'informer les user de la fermeure du channel
channel::~channel(void) {}