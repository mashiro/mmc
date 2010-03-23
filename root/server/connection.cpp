#include "connection.hpp"
#include "command/command.hpp"
#include <boost/bind.hpp>
#include <vector>
#include <algorithm>

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

Connection::streambuf_type& Connection::streambuf()
{
	return streambuf_;
}

const Connection::streambuf_type& Connection::streambuf() const
{
	return streambuf_;
}

std::string& Connection::buffer()
{
	return buffer_;
}

const std::string& Connection::buffer() const
{
	return buffer_;
}

void Connection::start()
{
	async_read(boost::bind(&Connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void Connection::shutdown()
{
	boost::system::error_code ignored_ec;
	socket_.shutdown(socket_type::shutdown_both, ignored_ec);
}

void Connection::read_streambuf(std::size_t bytes_transferred)
{
	const char* data = boost::asio::buffer_cast<const char*>(streambuf_.data());
	streambuf_.consume(bytes_transferred);
	buffer_.assign(data, data + bytes_transferred - 2);
}

void Connection::async_write_result()
{
	async_write(boost::asio::buffer(buffer_),
		boost::bind(&Connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error));
}

void Connection::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		read_streambuf(bytes_transferred);

		CommandPtr command = Command::parse(buffer_);
		if (command)
		{
			command->execute(shared_from_this());
		}
		else
		{
			buffer_ += constant::crlf;
			async_write(boost::asio::buffer(buffer_),
				boost::bind(&Connection::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}
}

void Connection::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		shutdown();
	}
}

} // namespace mmc
