#include "Server.hpp"


static void get_source(s_parser_data& source, std::string& data)
{
	size_t	pos1;
	size_t	pos2;

	pos1 = data.find_first_of("!@");
	if (pos1 == std::string::npos)
	{
		source.nickname = data;
		return ;
	}
	source.nickname = data.substr(0, pos1);
	if (data[pos1] == '!')
	{
		pos2 = data.find("@", pos1 + 1);
		if (pos2 == std::string::npos)
			source.user = data.substr(pos1 + 1, data.size());
		else
		{
			source.user = data.substr(pos1 + 1, pos2 - pos1 - 1);
			source.host = data.substr(pos2 + 1, data.size());
		}
	}
	else if (data[pos1] == '@')
		source.host = data.substr(pos1 + 1, data.size());
}

static size_t skip_space(size_t index, const std::string& str)
{
	while (index < str.size() && std::isspace(str[index])) 
		index++;
	return index;
}

void get_cmd(std::vector<std::string>& cmd, const std::string& str)
{
	size_t str_size = str.size();
	size_t index = 0;
	size_t pos_start = 0;

	while (index < str_size)
	{
		index = skip_space(index, str);
		if (index >= str_size)
			break;

		pos_start = index;
		while (index < str_size && !std::isspace(str[index])) 
			index++;

		if (str[pos_start] == ':')
		{
			cmd.push_back(str.substr(pos_start + 1));
			return;
		}
		cmd.push_back(str.substr(pos_start, index - pos_start));
	}
}



inline void	get_data(t_parser_data& data, std::string& str)
{
	size_t	pos = 0;
	size_t	index = 0;
	size_t  size = str.size();


	if (str.empty())
		throw std::runtime_error("Empty input string");
	index = skip_space(index, str);
	if (index < size && str[index] == '@') 
	{
		index++;
		while (index < size && !std::isspace(str[index])) 
			index++;
	}
	index = skip_space(index, str);

	if (index < size && str[index] == ':')// source
	{
		pos = str.find(' ', index);
		if (pos == std::string::npos)
			throw std::runtime_error("Syntax error: Missing space after source");
		std::string cut = str.substr(index + 1, pos - index - 1);
		get_source(data, cut);
		index += pos + 1;
	}
	index = skip_space(index, str);
	if (index < str.size()) 
		get_cmd(data.cmd, str.substr(index));
	else
		throw std::runtime_error("Syntax error: Missing command");
}

static	void clear_data(t_parser_data& data)
{
	std::vector<std::string>::iterator it;

	data.tag.clear();
	data.nickname.clear();
	data.user.clear();
	data.host.clear();
	it = data.cmd.begin();
	for (; it != data.cmd.end(); it++)
		(*it).clear();
	data.cmd.clear();
}

void	Server::parser(std::string& str, User* &user)
{
	static t_parser_data data;
	static std::vector<std::string>::iterator it;


	size_t	pos_begin = 0;
	size_t	pos_end   = 0;

	std::string	tmp_str;
	pos_end = str.find_first_of("\r\n", pos_begin);
	if (pos_end == std::string::npos)
		return;

	while (1)
	{
		clear_data(data);

		pos_end = str.find_first_of("\r\n", pos_begin);
		if (pos_end == std::string::npos)
		{
			str = str.substr(pos_begin, str.size());
			break;
		}

		tmp_str = str.substr(pos_begin, pos_end - pos_begin);

		get_data(data, tmp_str);

		pos_begin = pos_end + ((str[pos_end] == '\r' || str[pos_end] == '\n') && str[pos_end + 1] != '\n' ? 1 : 2);

		if (data.cmd.size() != 0)
			exec_cmd(data, user);

		str.clear();
	}
}
