#include "Server.hpp"


static std::vector<std::string>& get_source(size_t& index, std::string& data)
{
	// TODO only work when perfect data
	static std::vector<std::string> source(3);

	size_t	pos1;
	size_t	pos2;

	source.clear();

	pos1 = data.find_first_of("!@", index, data.size());
	if (pos1 == std::string::npos)
	{
		source[0] = data.substr(index, data.size());
	}
	else
	{
		source[0] = data.substr(index, pos1);
		if (data[pos1] == '!')
		{
			pos2 = data.find("@", pos1 + 1, data.size());
			if (pos2 == std::string::npos)
			{
				source[1] = data.substr(pos1, data.size());
			}
			else
			{
				/* code */
			}
			
		}
		else if (data[pos1] == '@')
		{
			source[2] = data.substr(index, pos1);
		}
	}
	return (source);
}

void	parser(std::string& data)
{
	std::vector<std::string> source; /* <nickname> [ "!" <user> ] [ "@" <host> ] */
	std::vector<std::string> cmd;


	// TODO split par separateur '\r\n'

	size_t	size  = data.size();
	size_t	pos = 0;
	size_t	index = 0;

	//TODO veif size limit
	while (data[index] == ' ')
	{
		index++;
	}
	if (data[index] == '@')
	{
		// take tage
	}
	while (data[index] == ' ')
	{
		index++;
	}
	if (data[index] == ':')
	{
		pos = data.find(' ', index);
		if (pos == std::string::npos)
		{
			source = get_source(index, data);
		}
		else
		{
			// source = get_source(index, data.substr());
		}
		
		
	}

	// take cmd + para
}