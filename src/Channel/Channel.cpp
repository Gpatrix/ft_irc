#include "Channel.hpp"

Channel::Channel(std::string name, id_t owner): _Name(name)
{
	this->_Operators.push_back(owner);
	this->_User.push_back(owner);
}

// TODO voir ci besoi d'informer les User de la fermeure du Channel
Channel::~Channel(void) {}