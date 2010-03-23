#ifndef MMC_CACHE_HPP_INCLUDED
#define MMC_CACHE_HPP_INCLUDED

#include <boost/noncopyable.hpp>

namespace mmc {

class CacheBase
	: private boost::noncopyable
{
public:
};

class Cache
	: private boost::noncopyable
{
public:
	Cache();
};

} // namespace mmc

#endif /* MMC_CACHE_HPP_INCLUDED */
