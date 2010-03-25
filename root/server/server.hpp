#ifndef MMC_SERVER_HPP_INCLUDED
#define MMC_SERVER_HPP_INCLUDED

#include "asio_base.hpp"
#include "shared_object.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <string>

namespace mmc {

MMC_FWD_DECL_CLASS(Connection)
MMC_FWD_DECL_CLASS(CacheBase)

class Server
	: public AsioBase
	, public SharedObject
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
	MMC_ENABLE_SHARED_THIS(Server)

	explicit Server(const std::string& address, const std::string& port, std::size_t thread_pool_size);
	virtual ~Server();

	void start();
	void stop();

public:
	MMC_PROPERTY_DEF(CacheBasePtr, cache)

private:
	void async_accept();
	void handle_accept(ConnectionPtr connection, const boost::system::error_code& error);

private:
	io_service_type io_service_;
	acceptor_type acceptor_;
	std::size_t thread_pool_size_;
};

} // namespace mmc

#endif /* MMC_SERVER_HPP_INCLUDED */
