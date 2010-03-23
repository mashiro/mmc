#ifndef MMC_CONFIG_HPP_INCLUDED
#define MMC_CONFIG_HPP_INCLUDED

#include <string>
#include <boost/cstdint.hpp>

namespace mmc {

typedef boost::uint32_t cache_flags_type;
typedef boost::uint32_t cache_exptime_type;
typedef boost::uint32_t cache_bytes_type;
typedef boost::uint64_t cache_cas_type;

} // namespace mmc

#endif /* MMC_CONFIG_HPP_INCLUDED */
