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
const std::string&			Channel::getName(void)				const	{return (this->_Name);}
const std::string&			Channel::getTopic(void)				const	{return (this->_Topic);}
const std::string&			Channel::getTopic_modif_user(void)	const	{return (this->_Topic_modif_user);};
const std::time_t&			Channel::getTopic_modif_time(void)	const	{return (this->_Topic_modif_time);};
const std::string&			Channel::getPasword(void)			const	{return (this->_Key);}
const bool&				Channel::isInvitationOnly(void)		const	{return (this->_invitationOnly);}
const bool&				Channel::isProtectedTopic(void)		const	{return (this->_protectedTopic);}
const size_t&				Channel::getUserLimit(void)			const	{return (this->_userLimit);}
const std::vector<id_t>&	Channel::getUsers(void)				const	{return (this->_Users);}
const std::vector<id_t>&	Channel::getOperators(void)			const	{return (this->_Operators);}
const std::vector<id_t>&	Channel::getInvitation(void)		const	{return (this->_Invitation);}

bool	Channel::isFull(void) const
{
	if (this->_Users.size() == this->_userLimit && this->_userLimit != 0)
		return (true);
	return (false);
}

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

bool Channel::isUser(const id_t& user_id) const
{
	for (size_t i = 0; i < this->_Users.size(); i++)
	{
		if (this->_Users[i] == user_id)
			return (true);
	}
	return (false);
}

bool Channel::isOperator(const id_t& user_id) const
{
	for (size_t i = 0; i < this->_Operators.size(); i++)
	{
		if (this->_Operators[i] == user_id)
			return (true);
	}
	return (false);
}

bool Channel::addUser(const id_t& user_id)
{
	if (this->_Users.size() < this->_userLimit || this->_userLimit == 0)
	{
		if (!isUser(user_id))
			this->_Users.push_back(user_id);
		return (false);
	}
	return (true);
}

bool Channel::removeUser(const id_t& user_id)
{
	const size_t size = this->_Users.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (this->_Users[i] == user_id)
		{
			this->_Users.erase(this->_Users.begin() + i);
			return (true);
		}
	}
	return (false);
}

void Channel::addOperator(const id_t& user_id)
{
	if (!isOperator(user_id))
		_Operators.push_back(user_id);
}

void Channel::removeOperator(const id_t& user_id)
{
	for (size_t i = 0; i < _Operators.size(); ++i)
	{
		if (_Operators[i] == user_id)
		{
			_Operators.erase(_Operators.begin() + i);
			return;
		}
	}
}

bool	Channel::isInvited(const id_t& user_id) const
{
	const size_t size = this->_Invitation.size();

	for (size_t index = 0; index < size; index++)
	{
		if (this->_Invitation[index] == user_id)
			return (true);
	}
	return (false);
}

void	Channel::addInvitation(const id_t& user_id)
{
	if (!this->isInvited(user_id))
		this->_Invitation.push_back(user_id);
}

void	Channel::removeInvitation(const id_t& user_id)
{
	const size_t size = this->_Invitation.size();

	for (size_t index = 0; index < size; index++)
	{
		if (this->_Invitation[index] == user_id)
		{
			this->_Invitation.erase(this->_Invitation.begin() + index);
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


std::string Channel::getModeString() const
{
	std::string modes;

	if (_invitationOnly)
		modes += "i";
	if (_protectedTopic)
		modes += "t";
	if (!_Key.empty())
		modes += "k";
	if (_userLimit > 0)
		modes += "l";
	return modes;
}

std::string Channel::getModeArgs() const
{
    std::string args;
    if (!_Key.empty()) {
        args += " " + _Key;
    }
    if (_userLimit > 0) {
        std::ostringstream oss;
        oss << _userLimit;
        args += " " + oss.str();
    }
    return args;
}
