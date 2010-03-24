#ifndef MMC_CACHE_BASE_HPP_INCLUDED
#define MMC_CACHE_BASE_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>

namespace mmc {

MMC_ENUM_BEGIN(ResultCode)
	stored,
	not_stored,
	exists,
	not_found,
	deleted,
MMC_ENUM_END()

MMC_FWD_DECL_CLASS(StorageCommand)
MMC_FWD_DECL_CLASS(CacheBase)

class CacheBase
	: private boost::noncopyable
{
public:
	// storage
	virtual bool set(const StorageCommand& command, const std::string& data) = 0;
};

} // namespace mmc

#endif /* MMC_CACHE_BASE_HPP_INCLUDED */
