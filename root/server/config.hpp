#ifndef MMC_CONFIG_HPP_INCLUDED
#define MMC_CONFIG_HPP_INCLUDED

#include "enum.hpp"
#include <string>
#include <boost/cstdint.hpp>

namespace mmc {

const std::string mmc_version = "0.1";

typedef boost::uint64_t cache_decimal_type;
typedef boost::uint32_t cache_flags_type;
typedef boost::uint32_t cache_exptime_type;
typedef boost::uint32_t cache_bytes_type;
typedef boost::uint64_t cache_cas_type;


MMC_ENUM_BEGIN(ResultCode)
	none,
	stored,
	not_stored,
	exists,
	not_found,
	deleted,
MMC_ENUM_END()

MMC_ENUM_BEGIN(CommandType)
	none, 
	set, add, replace, append, prepend, cas,
	get, gets,
	delete_,
	incr, decr,
	version, quit,
MMC_ENUM_END()


namespace constant {

// global
const std::string crlf    = "\r\n";
const std::string empty   = "";
const std::string space   = " ";
const std::string noreply = "noreply";

namespace command {
	// storage
	const std::string set     = "set";
	const std::string add     = "add";
	const std::string replace = "replace";
	const std::string append  = "append";
	const std::string prepend = "prepend";
	const std::string cas     = "cas";

	// retrieval
	const std::string get     = "get";
	const std::string gets    = "gets";

	// deletion
	const std::string delete_ = "delete";

	// incr/decr
	const std::string incr    = "incr";
	const std::string decr    = "decr";

	// other
	const std::string version = "version";
	const std::string quit    = "quit";
} 

namespace result {
	const std::string error        = "ERROR";
	const std::string client_error = "CLIENT_ERROR";
	const std::string server_error = "SERVER_ERROR";
	const std::string stored       = "STORED";
	const std::string not_stored   = "NOT_STORED";
	const std::string exists       = "EXISTS";
	const std::string not_found    = "NOT_FOUND";
	const std::string deleted      = "DELETED";
	const std::string value        = "VALUE";
	const std::string end          = "END";
	const std::string version      = "VERSION";
}

} // namespace constant

} // namespace mmc

#endif /* MMC_CONFIG_HPP_INCLUDED */
