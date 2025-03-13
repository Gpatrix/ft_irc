#pragma once
#include "User.hpp"
#include <iostream>
#include <sys/types.h>
#include <vector>
#include <sstream> 
#include <map>

#define CHANNEL_KEY_SIZE_LIMIT 50
#define CHANNEL_NAME_SIZE_LIMIT 200



class Channel
{
	private:
		std::string			_Name;
		std::string			_Topic;
		std::vector<id_t>	_Users;
		std::vector<id_t>	_Operators;
		std::string			_Key;
	
		bool				_invitationOnly;
		bool				_protectedTopic;
		bool				_isvid;	
		size_t				_userLimit;

	public:
		Channel(std::string Name, id_t owner);
		~Channel(void);

		// Getters
		std::string			getName(void) const;
		std::string			getTopic(void) const;
		std::string 		getPasword(void) const;
		std::vector<id_t> 	getUser(void) const;
		std::vector<id_t> 	getUserOP(void) const;
		bool				isInvitationOnly(void) const;
		bool				isProtectedTopic(void) const;
		bool				getIsVid() const { return _isvid; }
		size_t				getUserLimit(void) const;

		// Setters
		void	setTopic(std::string topic);
		void	setKey(std::string Key);
		void	freeKey(void);
		void	setInvitationOnly(bool mode);
		void	setProtectedTopic(bool mode);
		void	setUserLimit(size_t limit);

		// User management
		bool	isUser(const id_t& user) const;
		bool	addUser(const id_t& user);
		bool	removeUser(const id_t& user);

		bool	isOperator(const id_t& user) const;
		void	addOperator(const id_t& user);
		void	removeOperator(const id_t& user);

		bool 	isMember(const id_t& user);
		std::string getChannelSymbol() const;
		std::vector<std::string> getUserList(std::vector<User*>& user);
};