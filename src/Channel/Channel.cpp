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
}

// Destructeur
Channel::~Channel(void) {}

// Getters
std::string			Channel::getName(void) const				{return (this->_Name);}
std::string			Channel::getTopic(void) const				{return (this->_Topic);}
std::string			Channel::getTopic_modif_user(void) const	{return (this->_Topic_modif_user);};
std::time_t			Channel::getTopic_modif_time(void) const	{return (this->_Topic_modif_time);};
std::string			Channel::getPasword(void) const				{return (this->_Key);}
bool				Channel::isInvitationOnly(void) const		{return (this->_invitationOnly);}
bool				Channel::isProtectedTopic(void) const		{return (this->_protectedTopic);}
size_t				Channel::getUserLimit(void) const			{return (this->_userLimit);}
std::vector<id_t>	Channel::getUsers(void) const				{return (this->_Users);}
std::vector<id_t>	Channel::getOperators(void) const				{return (this->_Operators);}

// Setters
void	Channel::setTopic(const std::string& topic)	{this->_Topic = topic;}
void	Channel::setTopicModifUser(const std::string& topic_modif_user) {this->_Topic_modif_user = topic_modif_user;}
void	Channel::setTopicModifTime(const std::time_t& topic_modif_time) {this->_Topic_modif_time = topic_modif_time;}
void	Channel::setInvitationOnly(bool mode)	{this->_invitationOnly = mode;}
void	Channel::setProtectedTopic(bool mode)	{this->_protectedTopic = mode;}
void	Channel::setUserLimit(size_t limit)		{this->_userLimit = limit;}

void Channel::setKey(const std::string& key)
{
	if (key.size() <= CHANNEL_KEY_SIZE_LIMIT)
		_Key = key;
	else
		std::cerr << "Key exceeds size limit." << std::endl;
}

void Channel::clearKey()
{
	this->_Key.clear();
}

bool Channel::isUser(const id_t& user) const
{
	for (size_t i = 0; i < this->_Users.size(); i++)
	{
		if (this->_Users[i] == user)
			return (true);
	}
	return (false);
}

bool Channel::isOperator(const id_t& user) const
{
	for (size_t i = 0; i < this->_Operators.size(); i++)
	{
		if (this->_Operators[i] == user)
			return (true);
	}
	return (false);
}

bool Channel::addUser(const id_t& user)
{
	if (this->_Users.size() < this->_userLimit || this->_userLimit == 0)
	{
		if (!isUser(user))
			this->_Users.push_back(user);
		return (false);
	}
	return (true);
}

bool Channel::removeUser(const id_t& user)
{
	for (size_t i = 0; i < _Users.size(); ++i)
	{
		if (_Users[i] == user)
		{
			_Users.erase(_Users.begin() + i);
			if (_Users.empty())
				_isempty = true;
			return (true);
		}
	}
	return (false);
}

void Channel::addOperator(const id_t& user)
{
	if (!isOperator(user))
		_Operators.push_back(user);
}

void Channel::removeOperator(const id_t& user)
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
	for (size_t i = 0; i < this->_Users.size(); ++i)
	{
		std::ostringstream user;
		bool isOperator = false;
		for (size_t j = 0; j < this->_Operators.size(); ++j)
		{
			if (_Users[i] == this->_Operators[j])
			{
				isOperator = true;
				break;
			}
		}
		if (isOperator)
			user << "@";

		static	std::vector<User *>::iterator it;
		it = Vuser.begin();
		for (; it != Vuser.end(); it++)
		{
			if ((*it)->get_id() == this->_Users[i])
			{
				userList.push_back(user.str());
				break;
			}
		}

		userList.push_back(user.str());
	}

	return (userList);
}


