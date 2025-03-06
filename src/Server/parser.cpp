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

void	parser(std::string& data)
{
	std::vector<std::string> tag;
	std::vector<std::string> source(3); /* <nickname> [ "!" <user> ] [ "@" <host> ] */
	std::vector<std::string> cmd;


	// TODO split par separateur '\r\n'
	// si pas ne pas parse

	// size_t	size  = data.size();
	size_t	pos = 0;
	size_t	index = 0;

	//TODO veif size limit

	// for better parsing split with SPACE ' '

	while (data[index] == ' ')
	{
		index++;
	}
	if (data[index] == '@')// tage
	{
		while (data[index] != ' ')
		{
			index++;
		}
	}
	while (data[index] == ' ')
	{
		index++;
	}
	if (data[index] == ':')// source
	{
		pos = data.find(' ', index);
		if (pos == std::string::npos)
		{
			throw std::runtime_error("Syntaxe error");
		}
		else
		{
			std::string cut = data.substr(index + 1, pos - index - 1);
			std::cout << "cut: " << cut << '\n';
			get_source(source, cut);
			index += cut.size() + 1;
		}
	}
	while (data[index] == ' ')
	{
		index++;
	}
	cmd.push_back(data.substr(index, data.size()));

	std::cout
	<< "nickname: " << source[0] << '\n'
	<< "user    : " << source[1] << '\n'
	<< "host    : " << source[2] << '\n';


	for (std::vector<std::string>::iterator it = cmd.begin(); it < cmd.end(); it++)
	{
		std::cout << "cmd: " << *it << '\n';
	}
	
	// data.find(' ', index);


	// take cmd + para
}