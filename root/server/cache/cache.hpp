#ifndef MMC_CACHE_HPP_INCLUDED
#define MMC_CACHE_HPP_INCLUDED

#include "cache/cache_base.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

namespace mmc {

MMC_FWD_DECL_CLASS(Cache)

class Cache : public CacheBase
{
public:
	typedef std::string key_type;
	typedef CacheRecord value_type;
	typedef std::pair<const key_type, value_type> mapped_type;
	typedef std::allocator<mapped_type> allocator_type;
	typedef boost::unordered_map<
		key_type, value_type, boost::hash<key_type>, std::equal_to<key_type>, allocator_type
	> map_type;
	typedef map_type::iterator iterator;
	typedef map_type::const_iterator const_iterator;
	typedef boost::shared_mutex shared_mutex_type;
	typedef boost::shared_lock<shared_mutex_type> shared_lock_type; 
	typedef boost::unique_lock<shared_mutex_type> unique_lock_type; 
	typedef boost::shared_ptr<cache_cas_type> atomic_cas_type;

public:
	Cache();
	virtual ~Cache();

public:
	// storage
	virtual ResultCode::type set(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data);
	virtual ResultCode::type add(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data);
	virtual ResultCode::type replace(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data);
	virtual ResultCode::type append(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data);
	virtual ResultCode::type prepend(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data);
	virtual ResultCode::type cas(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, cache_cas_type cas, const std::string& data);

	// retrieval
	virtual boost::optional<CacheRecord> get(const std::string& key) const;
	virtual boost::optional<CacheRecord> gets(const std::string& key) const;

private:
	cache_cas_type get_next_cas();

private:
	mutable shared_mutex_type mutex_;
	map_type map_;
	atomic_cas_type cas_;
};

} // namespace mmc

#endif /* MMC_CACHE_HPP_INCLUDED */
