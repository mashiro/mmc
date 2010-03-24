#ifndef MMC_CACHE_HPP_INCLUDED
#define MMC_CACHE_HPP_INCLUDED

#include "cache_base.hpp"
#include <boost/unordered_map.hpp>

namespace mmc {

MMC_FWD_DECL_CLASS(Cache)

class CacheRecord
{
public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(std::string, data)
	MMC_PROPERTY_DEF(cache_flags_type, flags)
	MMC_PROPERTY_DEF(cache_exptime_type, exptime)
	MMC_PROPERTY_DEF(cache_cas_type, cas)
};

class Cache : public CacheBase
{
public:
	typedef boost::unordered_map<std::string, CacheRecord> map_type;

public:
	Cache();

	virtual bool set(const StorageCommand& command, const std::string& data);

private:
	map_type map_;
};

} // namespace mmc

#endif /* MMC_CACHE_HPP_INCLUDED */
