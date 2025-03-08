#include "Server.hpp"

// https://modern.ircdocs.horse/
// https://www.rfc-editor.org/rfc/rfc1459.html
// https://dd.ircdocs.horse/

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	Server	the_server;

	try
	{
		the_server.init(argv[1], argv[2]);
		the_server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
