#include "server.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 4)
		{
			std::cerr << "Usage: mmc <address> <port> <threads>" << std::endl;
			return 1;
		}

		std::cout << "mmc is running..." << std::endl;

		mmc::Server server(argv[1], argv[2], boost::lexical_cast<std::size_t>(argv[3]));
		server.start();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
