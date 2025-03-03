#include "server.hpp"

// https://modern.ircdocs.horse/
// https://www.rfc-editor.org/rfc/rfc1459.html

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "usage: ./ircserv <port> <password>";
		return (1);
	}

	try
	{
		server(argv[1], argv[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
