#include "Server.hpp"


static void get_source(s_parser_data& source, std::string& data)
{
	// TODO only work when perfect data

	size_t	pos1;
	size_t	pos2;

	pos1 = data.find_first_of("!@");
	if (pos1 == std::string::npos)
	{
		source.nickname = data;
	}
	else
	{
		source.nickname = data.substr(0, pos1);
		if (data[pos1] == '!')
		{
			pos2 = data.find("@", pos1 + 1);
			if (pos2 == std::string::npos)
			{
				source.user = data.substr(pos1 + 1, data.size());
			}
			else
			{
				source.user = data.substr(pos1 + 1, pos2 - pos1 - 1);
				source.host = data.substr(pos2 + 1, data.size());
			}
		}
		else if (data[pos1] == '@')
		{
			source.host = data.substr(pos1 + 1, data.size());
		}
	}
}

void	get_cmd(std::vector<std::string>&cmd, const std::string& str)
{
	size_t	str_size = str.size();
	size_t	index = 0;
	size_t	pos_start = 0;

	while (true)
	{
		while (index < str_size && str[index] == ' ')
			index++;

		pos_start = index;
		
		while (index < str_size && str[index] != ' ')
			index++;

		if (index >= str_size)
		{
			if (index - pos_start != 0)
				cmd.push_back(str.substr(pos_start, str_size));
			return;
		}

		if (str[pos_start] == ':')
		{
			cmd.push_back(str.substr(pos_start + 1, str_size));
			return;
		}
		
		cmd.push_back(str.substr(pos_start, index - pos_start));
		index++;
	}
}

inline void	get_data(t_parser_data& data, std::string str)
{
	size_t	pos = 0;
	size_t	index = 0;

	std::string	tmp_part;

	//TODO veif size limit

	// for better parsing split with SPACE ' '

	while (str[index] == ' ')
	{
		index++;
	}
	if (str[index] == '@')// tage
	{
		while (str[index] != ' ')
		{
			index++;
		}
	}
	while (str[index] == ' ')
	{
		index++;
	}
	if (str[index] == ':')// source
	{
		pos = str.find(' ', index);
		if (pos == std::string::npos)
		{
			throw std::runtime_error("Syntaxe error");
		}
		else
		{
			std::string cut = str.substr(index + 1, pos - index - 1);
			get_source(data, cut);
			index += cut.size() + 1;
		}
	}
	while (str[index] == ' ')
	{
		index++;
	}
	if (str[index] == *(str.end() - 1))
	{
		throw std::runtime_error("Syntaxe error");
	}

	get_cmd(data.cmd, str.substr(index, str.size()));
}

void	Server::parser(std::string& str, User* &user)
{
	static t_parser_data data;


	size_t	pos_begin = 0;
	size_t	pos_end   = 0;

	std::string	tmp_str;

	pos_end = str.find_first_of("\r\n", pos_begin);
	if (pos_end == std::string::npos)
		return;

	// TODO only work on perfect separator not single '\r' or '\n'
	while (1)
	{
		data.tag.clear();
		data.nickname.clear();
		data.user.clear();
		data.host.clear();
		data.cmd.clear();

		pos_end = str.find_first_of("\r\n", pos_begin);
		
		if (pos_end == std::string::npos)
		{
			str = str.substr(pos_begin, str.size());
			break;
		}

		tmp_str = str.substr(pos_begin, pos_end - pos_begin);

		// std::cout << '\'' << tmp_str << "\'\n";

		get_data(data, tmp_str);

		pos_begin = pos_end + 2;

		if (!data.nickname.empty())
		{
			std::cout
			<< "nickname: " << data.nickname << '\n'
			<< "user    : " << data.user << '\n'
			<< "host    : " << data.host << '\n';
		}

		std::cout << "cmd: " << data.cmd[0] << '\n';
		for (std::vector<std::string>::iterator it = data.cmd.begin() + 1; it < data.cmd.end(); it++)
		{
			std::cout << "option: " << '\'' << *it << "\'\n";
		}
		if (data.cmd.size() != 0)
			exec_cmd(data, user);
	}
}