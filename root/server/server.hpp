#ifndef MMC_SERVER_HPP_INCLUDED
#define MMC_SERVER_HPP_INCLUDED

#include "asio_base.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <string>

namespace mmc {

MMC_FWD_DECL_CLASS(Connection)

class Server
	: public AsioBase
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

public:
	explicit Server(const std::string& address, const std::string& port, std::size_t thread_pool_size);

	void start();
	void stop();

private:
	void handle_accept(ConnectionPtr connection, const boost::system::error_code& error);
	void async_accept();

private:
	io_service_type io_service_;
	acceptor_type acceptor_;
	std::size_t thread_pool_size_;
};

} // namespace mmc

#endif /* MMC_SERVER_HPP_INCLUDED */
