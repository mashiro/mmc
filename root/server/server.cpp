#include "server.hpp"
#include "connection.hpp"
#include <boost/bind.hpp>
#include <boost/thread.hpp>

namespace mmc {

Server::Server(const std::string& address, const std::string& port, std::size_t thread_pool_size)
	: acceptor_(io_service_)
	, thread_pool_size_(thread_pool_size)
{
	resolver_type resolver(io_service_);
	resolver_type::query query(address, port);
	endpoint_type endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(acceptor_type::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	async_accept();
}

void Server::start()
{
	boost::thread_group threads;

	for (std::size_t i = 0; i < thread_pool_size_; ++i)
	{
		threads.create_thread(
			boost::bind(&io_service_type::run, &io_service_));
	}

	threads.join_all();
}

void Server::stop()
{
	io_service_.stop();
}

void Server::handle_accept(ConnectionPtr connection, const boost::system::error_code& error)
{
	if (!error)
	{
		connection->start();
		async_accept();
	}
}

void Server::async_accept()
{
	ConnectionPtr connection(new Connection(io_service_));

	acceptor_.async_accept(connection->socket(),
		boost::bind(&Server::handle_accept, this,
			connection,
			boost::asio::placeholders::error));
}

} // namespace mmc
