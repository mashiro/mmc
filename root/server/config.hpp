#ifndef MMC_CONFIG_HPP_INCLUDED
#define MMC_CONFIG_HPP_INCLUDED

#include "enum.hpp"
#include <string>
#include <boost/cstdint.hpp>

namespace mmc {

const std::string mmc_version = "0.1";

typedef boost::uint32_t cache_flags_type;
typedef boost::uint32_t cache_exptime_type;
typedef boost::uint32_t cache_bytes_type;
typedef boost::uint64_t cache_cas_type;
typedef boost::uint64_t mmc_decimal_type;

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
	version, quit,
MMC_ENUM_END()

} // namespace mmc

#endif /* MMC_CONFIG_HPP_INCLUDED */
