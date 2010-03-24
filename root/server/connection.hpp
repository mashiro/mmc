#ifndef MMC_CONNECTION_HPP_INCLUDED
#define MMC_CONNECTION_HPP_INCLUDED

#include "asio_base.hpp"
#include "constant.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

namespace mmc {

MMC_FWD_DECL_CLASS(CacheBase)
	
class Connection
	: public AsioBase
	, public boost::enable_shared_from_this<Connection>
	, private boost::noncopyable
{
public:
	explicit Connection(io_service_type& io_service, CacheBaseWeakPtr cache);

	socket_type& socket();
	const socket_type& socket() const;

	std::string& buffer();
	const std::string& buffer() const;

	CacheBasePtr get_cache() const;

	void start();
	void restart();
	void shutdown();

	// 非同期で読み込む
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
	std::string& read_streambuf(std::size_t bytes_transferred);

	// 非同期で書き込む
	template <typename ConstBufferSequence, typename WriteHandler>
	void async_write(const ConstBufferSequence& buffers, WriteHandler handler)
	{
		boost::asio::async_write(socket_, buffers, strand_.wrap(handler));
	}

	// 非同期で結果を書き込む
	template <typename ConstBufferSequence>
	void async_write_result(const ConstBufferSequence& buffers)
	{
		async_write(buffers, boost::bind(&Connection::handle_write_result, shared_from_this(),
			boost::asio::placeholders::error));
	}

	void async_write_result()
	{
		async_write_result(boost::asio::buffer(buffer_));
	}

private:
	void handle_read_command(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handle_write_result(const boost::system::error_code& error);

private:
	strand_type strand_;
	socket_type socket_;
	streambuf_type streambuf_;
	std::string buffer_;
	CacheBaseWeakPtr cache_;
};

} // namespace mmc

#endif /* MMC_CONNECTION_HPP_INCLUDED */
