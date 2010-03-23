#ifndef MMC_CACHE_HPP_INCLUDED
#define MMC_CACHE_HPP_INCLUDED

#include "cache_base.hpp"

namespace mmc {


MMC_FWD_DECL_CLASS(Cache)

class Cache : public CacheBase
{
public:
	Cache();

public:
	virtual bool set(const StorageCommand& command, const std::string& data) {}
};

} // namespace mmc

#endif /* MMC_CACHE_HPP_INCLUDED */
