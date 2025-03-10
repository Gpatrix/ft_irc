#include "Channel.hpp"

// Constructeur
Channel::Channel(std::string Name, id_t owner)
{
	if (Name.size() > CHANNEL_NAME_SIZE_LIMIT)
		_Name = Name.substr(0, CHANNEL_NAME_SIZE_LIMIT);
	else
		_Name = Name;

	_invitationOnly = false;
	_protectedTopic = false;
	_userLimit = 0;

	_Operators.push_back(owner);
	_Users.push_back(owner);
}

// Destructeur
// TODO voir ci besoi d'informer les User de la fermeure du Channel
Channel::~Channel(void) {}

// Getters
std::string Channel::getName(void) const {return _Name;}
std::string Channel::getTopic(void) const {return _Topic;}
std::string Channel::getPasword(void) const {return _Password;}
bool Channel::isInvitationOnly(void) const {return _invitationOnly;}
bool Channel::isProtectedTopic(void) const {return _protectedTopic;}
size_t Channel::getUserLimit(void) const {return _userLimit;}
std::vector<id_t> Channel::getUser(void) const { return _Users;}

// Setters
void Channel::setTopic(std::string topic) {_Topic = topic;}
void Channel::setInvitationOnly(bool mode) { _invitationOnly = mode;}
void Channel::setProtectedTopic(bool mode) {_protectedTopic = mode;}
void Channel::setUserLimit(size_t limit) {_userLimit = limit;}

void Channel::setPassword(std::string password)
{
	if (password.size() <= CHANNEL_PASSWORD_SIZE_LIMIT)
		_Password = password;
	else
		std::cerr << "Password exceeds size limit." << std::endl;
}

// User management
bool Channel::addUser(id_t user)
{
	if (_Users.size() < _userLimit)
	{
		_Users.push_back(user);
		return true;
	}
	return false;
}

bool Channel::removeUser(id_t user)
{
	for (size_t i = 0; i < _Users.size(); ++i)
	{
		if (_Users[i] == user)
		{
			_Users.erase(_Users.begin() + i);
			return true;
		}
	}
	return false;
}

bool Channel::isOperator(id_t user) const
{
	for (size_t i = 0; i < _Operators.size(); ++i)
	{
		if (_Operators[i] == user)
			return true;
	}
	return false;
}

void Channel::addOperator(id_t user)
{
	if (!isOperator(user))
		_Operators.push_back(user);
}

void Channel::removeOperator(id_t user)
{
	for (size_t i = 0; i < _Operators.size(); ++i)
	{
		if (_Operators[i] == user)
		{
			_Operators.erase(_Operators.begin() + i);
			return;
		}
	}
}

std::string Channel::getChannelSymbol() const
{
	if (_invitationOnly)
		return "@";
	if (_protectedTopic)
		return "+";
	return "";
}

std::vector<std::string> Channel::getUserList(std::vector<User*>& Vuser)
{
	std::vector<std::string> userList; 
	for (size_t i = 0; i < _Users.size(); ++i)
	{
		std::ostringstream user;
		bool isOperator = false;
		for (size_t j = 0; j < _Operators.size(); ++j)
		{
			if (_Users[i] == _Operators[j])
			{
				isOperator = true;
				break;
			}
		}
		if (isOperator)
			user << "@";

		user << Vuser[_Users[i]]->get_nickname();

		userList.push_back(user.str());
		
	}

	return userList;
}
