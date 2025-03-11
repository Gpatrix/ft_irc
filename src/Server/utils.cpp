#include "Server.hpp"

std::vector<std::string> Server::split(const std::string &str, char delimiter)
{
	std::vector<std::string> result;
	size_t pos_begin = 0, pos_end = 0;

	while ((pos_end = str.find(delimiter, pos_begin)) != std::string::npos)
	{
		result.push_back(str.substr(pos_begin, pos_end - pos_begin));
		pos_begin = pos_end + 1;
	}
	result.push_back(str.substr(pos_begin));
	return result;
}