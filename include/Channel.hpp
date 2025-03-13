#pragma once

#include "User.hpp"
#include <iostream>
#include <sys/types.h>
#include <vector>
#include <sstream> 
#include <map>
#include <ctime>

#define CHANNEL_KEY_SIZE_LIMIT 50
#define CHANNEL_NAME_SIZE_LIMIT 200

class Channel
{
	private:
		std::string			_Name;
		std::string			_Topic;
		std::string			_Topic_modif_user;
		std::time_t			_Topic_modif_time;
		std::vector<id_t>	_Users;
		std::vector<id_t>	_Operators;
		std::vector<id_t>	_Invitation;
		std::string			_Key;
	
		bool				_invitationOnly;
		bool				_protectedTopic;
		size_t				_userLimit;

	public:
		Channel(std::string Name, id_t owner);
		~Channel(void);

		// Getters
		const std::string& 		getModeString() const;
	  const std::string& 		getModeArgs() const;

		const std::string&			getName(void) const;
		const std::string&			getTopic(void) const;
		const std::string&			getTopic_modif_user(void) const;
		const std::time_t&			getTopic_modif_time(void) const;
		const std::string&			getPasword(void) const;
		const std::vector<id_t>&	getUsers(void) const;
		const std::vector<id_t>&	getOperators(void) const;
		const std::vector<id_t>&	getInvitation(void) const;
		const bool&				isInvitationOnly(void) const;
		const bool&				isProtectedTopic(void) const;
		const size_t&				getUserLimit(void) const;

		bool				isFull(void) const;

		// Setters
		void	setTopic(const std::string& topic);
		void	setTopicModifUser(const std::string& topic_modif_user);
		void	setTopicModifTime(const std::time_t& topic_modif_time);
		void	setKey(const std::string& Key);
		void	clearKey(void);
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

		bool	isInvited(const id_t& user) const;
		void	addInvitation(const id_t& user);
		void	removeInvitation(const id_t& user);


		std::string getChannelSymbol() const;
		std::vector<std::string> getUserList(std::vector<User*>& user);
};