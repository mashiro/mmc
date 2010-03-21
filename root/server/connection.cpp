#include "connection.hpp"
#include "command/command.hpp"
#include <boost/bind.hpp>
#include <vector>

namespace mmc {

Connection::Connection(io_service_type& io_service)
	: strand_(io_service)
	, socket_(io_service)
{}

Connection::socket_type& Connection::socket()
{
	return socket_;
}

const Connection::socket_type& Connection::socket() const
{
	return socket_;
}

Connection::buffer_type& Connection::buffer()
{
	return buffer_;
}

const Connection::buffer_type& Connection::buffer() const
{
	return buffer_;
}

void Connection::start()
{
	async_read_some(boost::asio::buffer(buffer_),
		boost::bind(&Connection::handle_read, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Connection::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		CommandPtr command = Command::parse(std::string(buffer_.begin(), buffer_.begin() + bytes_transferred));

		async_write(boost::asio::buffer(buffer_, bytes_transferred),
			boost::bind(&Connection::handle_write, shared_from_this(),
				boost::asio::placeholders::error));
	}
}

void Connection::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		boost::system::error_code ignored_ec;
		socket_.shutdown(socket_type::shutdown_both, ignored_ec);
	}
}

} // namespace mmc
