#include "Server.hpp"

static char* _get_time(void)
{
	static char timestamp[20];

	std::time_t t = std::time(0);
	std::tm* tm_info = std::localtime(&t);

	std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
	return (timestamp);
}

void	logError(const std::string& msg)
{
	std::clog << BLUE << "[" << _get_time() << "] [ERROR] " << msg << END;
}

void	log(const std::string& msg) 
{
	std::clog << GREEN <<"[" << _get_time() << "] " << msg << END;
}

void	logPerror(const std::string& msg)
{
	std::string error_msg = strerror(errno);

	std::clog << RED << "[" << _get_time() << "] [SERVER ERROR] " << msg + ": " + error_msg << END << '\n';
}