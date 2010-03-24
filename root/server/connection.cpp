#include "connection.hpp"
#include "cache_base.hpp"
#include "command/command.hpp"
#include <boost/bind.hpp>
#include <vector>
#include <algorithm>

namespace mmc {

Connection::Connection(io_service_type& io_service, CacheBaseWeakPtr cache)
	: strand_(io_service)
	, socket_(io_service)
	, cache_(cache)
{}

Connection::socket_type& Connection::socket()
{
	return socket_;
}

const Connection::socket_type& Connection::socket() const
{
	return socket_;
}

std::string& Connection::buffer()
{
	return buffer_;
}

const std::string& Connection::buffer() const
{
	return buffer_;
}

CacheBasePtr Connection::get_cache() const
{
	return cache_.lock();
}

void Connection::start()
{
	async_read(boost::bind(&Connection::handle_read_command, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void Connection::restart()
{
	start();
}

void Connection::shutdown()
{
	boost::system::error_code ignored_ec;
	socket_.shutdown(socket_type::shutdown_both, ignored_ec);
}

std::string& Connection::read_streambuf(std::size_t bytes_transferred)
{
	const char* data = boost::asio::buffer_cast<const char*>(streambuf_.data());
	streambuf_.consume(bytes_transferred);
	buffer_.assign(data, data + bytes_transferred - 2); // 終端の CRLF を除く
	return buffer_;
}

void Connection::handle_read_command(const boost::system::error_code& error, std::size_t bytes_transferred)
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
			// error
			buffer_ = constant::error;
			buffer_ += constant::crlf;
			async_write_result();
		}
	}
}

void Connection::handle_write_result(const boost::system::error_code& error)
{
	if (!error)
	{
		restart();
	}
}

} // namespace mmc
