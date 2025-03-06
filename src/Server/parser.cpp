#include "Server.hpp"


static std::vector<std::string>& get_source(std::string& data)
{
	// TODO only work when perfect data
	static std::vector<std::string> source(3);
	size_t	my_index = 0;

	size_t	pos1;
	size_t	pos2;

	source.clear();

	pos1 = data.find_first_of("!@", my_index, data.size());
	if (pos1 == std::string::npos)
	{
		source[0] = data.substr(my_index, data.size());
	}
	else
	{
		source[0] = data.substr(my_index, pos1);
		if (data[pos1] == '!')
		{
			pos2 = data.find("@", pos1 + 1, data.size());
			if (pos2 == std::string::npos)
			{
				source[1] = data.substr(pos1, data.size());
			}
			else
			{
				source[1] = data.substr(pos1, pos2);
				source[2] = data.substr(pos2, data.size());
			}
			
		}
		else if (data[pos1] == '@')
		{
			source[2] = data.substr(pos1, data.size());
		}
	}
	return (source);
}

void	parser(std::string& data)
{
	std::vector<std::string> tag;
	std::vector<std::string> source; /* <nickname> [ "!" <user> ] [ "@" <host> ] */
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
		pos = data.find_first_of(' ', index);
		std::clog << "DEBUG: not cut  source: " << &data[index] << '\n';
		if (pos == std::string::npos)
		{
			throw std::runtime_error("Syntaxe error");
		}
		else
		{
			std::string cut = data.substr(index, pos - 1);
			std::clog << "DEBUG: not cut  source: " << &data[index] << '\n';
			std::clog << "DEBUG: cut source     : " << cut << '\n';
			source = get_source(cut);
			index += cut.size();
		}
	}

	cmd.push_back(data.substr(index, data.size()));

	for (std::vector<std::string>::iterator it = cmd.begin(); it < cmd.end(); it++)
	{
		std::cout << "cmd: " << *it << '\n';
	}
	
	// data.find(' ', index);


	// take cmd + para
}