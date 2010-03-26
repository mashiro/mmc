#ifndef MMC_CACHE_BASE_HPP_INCLUDED
#define MMC_CACHE_BASE_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

namespace mmc {

MMC_FWD_DECL_CLASS(CacheRecord)
MMC_FWD_DECL_CLASS(CacheBase)

class CacheRecord
{
public:
	MMC_PROPERTY_DEF(std::string, data)
	MMC_PROPERTY_DEF(cache_flags_type, flags)
	MMC_PROPERTY_DEF(cache_exptime_type, exptime)
	MMC_PROPERTY_DEF(cache_cas_type, cas)
};

class CacheBase
	: private boost::noncopyable
{
public:
	CacheBase();
	virtual ~CacheBase();

public:
	// storage
	virtual ResultCode::type set(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data) = 0;
	virtual ResultCode::type add(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data) = 0;
	virtual ResultCode::type replace(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data) = 0;
	virtual ResultCode::type append(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data) = 0;
	virtual ResultCode::type prepend(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data) = 0;
	virtual ResultCode::type cas(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, cache_cas_type cas, const std::string& data) = 0;

	// retrieval
	virtual boost::optional<CacheRecord> get(const std::string& key) const = 0;
	virtual boost::optional<CacheRecord> gets(const std::string& key) const = 0;

	// deletion
	virtual ResultCode::type delete_(const std::string& key, cache_exptime_type time) = 0;
};

} // namespace mmc

#endif /* MMC_CACHE_BASE_HPP_INCLUDED */
