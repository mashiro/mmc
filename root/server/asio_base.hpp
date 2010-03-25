#ifndef MMC_ASIOBASE_HPP_INCLUDED
#define MMC_ASIOBASE_HPP_INCLUDED

#include "utility.hpp"
#include <boost/asio.hpp>

namespace mmc {

class AsioBase
	: public boost::enable_shared_from_this<AsioBase>
{
public:
	MMC_ENABLE_SHARED_THIS(AsioBase)

	AsioBase() {}
	virtual ~AsioBase() {}

public:
	typedef boost::asio::io_service io_service_type;
	typedef boost::asio::io_service::strand strand_type;
	typedef boost::asio::streambuf streambuf_type;
	typedef boost::asio::ip::tcp protocol_type;
	typedef protocol_type::socket socket_type;
	typedef protocol_type::acceptor acceptor_type;
	typedef protocol_type::endpoint endpoint_type;
	typedef protocol_type::resolver resolver_type;
};

} // namespace mmc

#endif /* MMC_ASIOBASE_HPP_INCLUDED */
