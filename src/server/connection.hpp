#ifndef MMC_CONNECTION_HPP_INCLUDED
#define MMC_CONNECTION_HPP_INCLUDED

#include "asio_base.hpp"
#include "shared_object.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>

namespace mmc {

MMC_FWD_DECL_CLASS(CacheBase)
	
class Connection
	: public AsioBase
	, public SharedObject
	, private boost::noncopyable
{
public:
	MMC_ENABLE_SHARED_THIS(Connection)

	explicit Connection(io_service_type& io_service, CacheBaseWeakPtr cache);
	virtual ~Connection();

	socket_type& socket();
	const socket_type& socket() const;

	void start();
	void restart();
	void shutdown();

	CacheBasePtr get_cache() const;
	const std::string& get_buffer() const;

	std::size_t read_streambuf(std::size_t bytes_transferred);

	// 非同期で読み込む
	template <typename ReadHandler>
	void async_read(ReadHandler handler)
	{
		boost::asio::async_read_until(socket_, streambuf_, constant::crlf, strand_.wrap(handler));
	}

	// 非同期で書き込む
	template <typename ConstBufferSequence, typename WriteHandler>
	void async_write(const ConstBufferSequence& buffers, WriteHandler handler)
	{
		boost::asio::async_write(socket_, buffers, strand_.wrap(handler));
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
