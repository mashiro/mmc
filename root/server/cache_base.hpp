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
MMC_FWD_DECL_CLASS(CacheRecord)

class CacheRecord
{
public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(std::string, data)
	MMC_PROPERTY_DEF(cache_flags_type, flags)
	MMC_PROPERTY_DEF(cache_exptime_type, exptime)
	MMC_PROPERTY_DEF(cache_cas_type, cas)
};

class CacheBase
	: private boost::noncopyable
{
public:
	// storage
	virtual ResultCode::type set(const StorageCommand& command, const std::string& data) = 0;
	virtual ResultCode::type add(const StorageCommand& command, const std::string& data) = 0;
	virtual ResultCode::type replace(const StorageCommand& command, const std::string& data) = 0;
	virtual ResultCode::type append(const StorageCommand& command, const std::string& data) = 0;
	virtual ResultCode::type prepend(const StorageCommand& command, const std::string& data) = 0;
	virtual ResultCode::type cas(const StorageCommand& command, const std::string& data) = 0;
};

} // namespace mmc

#endif /* MMC_CACHE_BASE_HPP_INCLUDED */
