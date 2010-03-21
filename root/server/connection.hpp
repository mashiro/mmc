#ifndef MMC_CONNECTION_HPP_INCLUDED
#define MMC_CONNECTION_HPP_INCLUDED

#include "asio_base.hpp"
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace mmc {
	
class Connection
	: public AsioBase
	, public boost::enable_shared_from_this<Connection>
	, private boost::noncopyable
{
public:
	typedef AsioBase base;
	typedef base::io_service_type io_service_type;
	typedef base::strand_type strand_type;
	typedef base::protocol_type protocol_type;
	typedef base::socket_type socket_type;
	typedef base::acceptor_type acceptor_type;
	typedef base::endpoint_type endpoint_type;
	typedef base::resolver_type resolver_type;
	typedef boost::array<char, 1024 * 8> buffer_type;

public:
	explicit Connection(io_service_type& io_service);

	socket_type& socket();
	const socket_type& socket() const;

	buffer_type& buffer();
	const buffer_type& buffer() const;

	void start();

	template <typename Buffer, typename Handler>
	void async_read_some(Buffer buffer, Handler handler)
	{
		socket_.async_read_some(buffer, strand_.wrap(handler));
	}

	template <typename Buffer, typename Handler>
	void async_write(Buffer buffer, Handler handler)
	{
		boost::asio::async_write(socket_, buffer, strand_.wrap(handler));
	}

private:
	void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);

private:
	strand_type strand_;
	socket_type socket_;
	buffer_type buffer_;
};

} // namespace mmc

#endif /* MMC_CONNECTION_HPP_INCLUDED */
