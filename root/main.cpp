#include "server.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/cstdint.hpp>


int main(int argc, char* argv[])
{
	try
	{
		// parse program options
		namespace po = boost::program_options;
		po::options_description desc("allowed options");
		desc.add_options()
			("help,h", "print this help and exit")
			("address,l", po::value<std::string>()->default_value("0.0.0.0"), "interface to listen on")
			("port,p", po::value<boost::uint16_t>()->default_value(22122), "TCP port number to listen on")
			("threads,t", po::value<boost::uint32_t>()->default_value(1), "num threads")
			;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help"))
		{
			std::cout << desc << std::endl;
			return 1;
		}

		std::string address = vm["address"].as<std::string>();
		std::string port = boost::lexical_cast<std::string>(vm["port"].as<boost::uint16_t>());
		boost::uint32_t threads = vm["threads"].as<boost::uint32_t>();

		// show variables
		std::cout << "address: " << address << std::endl;
		std::cout << "port: " << port << std::endl;
		std::cout << "threads: " << threads << std::endl;

		// start server
		mmc::Server server(address, port, threads);
		server.start();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}

	return 0;
}
