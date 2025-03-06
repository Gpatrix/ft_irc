#include "Server.hpp"


static void get_source(std::vector<std::string>& source, std::string& data)
{
	// TODO only work when perfect data

	size_t	pos1;
	size_t	pos2;

	pos1 = data.find_first_of("!@");
	if (pos1 == std::string::npos)
	{
		source[0] = data;
	}
	else
	{
		source[0] = data.substr(0, pos1);
		if (data[pos1] == '!')
		{
			pos2 = data.find("@", pos1 + 1);
			if (pos2 == std::string::npos)
			{
				source[1] = data.substr(pos1 + 1, data.size());
			}
			else
			{
				source[1] = data.substr(pos1 + 1, pos2 - pos1 - 1);
				source[2] = data.substr(pos2 + 1, data.size());
			}
		}
		else if (data[pos1] == '@')
		{
			source[2] = data.substr(pos1 + 1, data.size());
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
			get_source(data.source, cut);
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
	t_parser_data data;

	// TODO dégueulasse
	data.source.push_back("");
	data.source.push_back("");
	data.source.push_back("");

	// size_t	size  = data.size();
	// size_t	pos = 0;
	// size_t	index = 0;

	// TODO split par separateur '\r\n'
	// pos = data.find_first_of("\r\n");
	

	// while (pos != std::string::npos)
	// {
		get_data(data, str);

		std::cout
		<< "nickname: " << data.source[0] << '\n'
		<< "user    : " << data.source[1] << '\n'
		<< "host    : " << data.source[2] << '\n';

		for (std::vector<std::string>::iterator it = data.cmd.begin(); it < data.cmd.end(); it++)
		{
			std::cout << "cmd: " << *it << '\n';
		}
	// }
	
	// data.find(' ', index);


	// take cmd + para
}