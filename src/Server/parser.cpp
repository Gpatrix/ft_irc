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

	data.cmd.push_back(str.substr(index, str.size()));
}

void	parser(std::string& str)
{
	static t_parser_data data;


	size_t	pos_begin = 0;
	size_t	pos_end   = 0;

	std::string	tmp_str;

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
			return;
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

		for (std::vector<std::string>::iterator it = data.cmd.begin(); it < data.cmd.end(); it++)
		{
			std::cout << "cmd: " << *it << '\n';
		}
	}

}