#ifndef MMC_CONNECTION_HPP_INCLUDED
#define MMC_CONNECTION_HPP_INCLUDED

#include "asio_base.hpp"
#include "constant.hpp"
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
	typedef base::streambuf_type streambuf_type;
	typedef base::protocol_type protocol_type;
	typedef base::socket_type socket_type;
	typedef base::acceptor_type acceptor_type;
	typedef base::endpoint_type endpoint_type;
	typedef base::resolver_type resolver_type;

public:
	explicit Connection(io_service_type& io_service);

	socket_type& socket();
	const socket_type& socket() const;

	streambuf_type& streambuf();
	const streambuf_type& streambuf() const;

	std::string& buffer();
	const std::string& buffer() const;

	void start();
	void shutdown();

	// read
	template <typename ReadHandler>
	void async_read(ReadHandler handler)
	{
		boost::asio::async_read_until(socket_, streambuf_, constant::crlf, strand_.wrap(handler));
	}

	template <typename Allocator, typename ReadHandler>
	void async_read(boost::asio::basic_streambuf<Allocator>& buffer, ReadHandler handler)
	{
		boost::asio::async_read_until(socket_, buffer, constant::crlf, strand_.wrap(handler));
	}

	// streambuf から buffer にデータを読み込む
	void read_streambuf(std::size_t bytes_transferred);

	// write
	template <typename ConstBufferSequence, typename WriteHandler>
	void async_write(const ConstBufferSequence& buffers, WriteHandler handler)
	{
		boost::asio::async_write(socket_, buffers, strand_.wrap(handler));
	}

	// buffer のデータを書き込みコネクションを閉じる
	void async_write_result();

private:
	void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);

private:
	strand_type strand_;
	socket_type socket_;
	streambuf_type streambuf_;
	std::string buffer_;
};

} // namespace mmc

#endif /* MMC_CONNECTION_HPP_INCLUDED */
