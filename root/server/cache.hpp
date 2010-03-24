#ifndef MMC_CACHE_HPP_INCLUDED
#define MMC_CACHE_HPP_INCLUDED

#include "cache_base.hpp"
#include <boost/unordered_map.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

namespace mmc {

MMC_FWD_DECL_CLASS(Cache)

class Cache : public CacheBase
{
public:
	typedef boost::unordered_map<std::string, CacheRecord> map_type;
	typedef map_type::iterator iterator;
	typedef map_type::const_iterator const_iterator;
	typedef boost::shared_mutex shared_mutex_type;
	typedef boost::shared_lock<shared_mutex_type> shared_lock_type; 
	typedef boost::unique_lock<shared_mutex_type> unique_lock_type; 

public:
	Cache();

	// storage
	virtual ResultCode::type set(const StorageCommand& command, const std::string& data);
	virtual ResultCode::type add(const StorageCommand& command, const std::string& data);
	virtual ResultCode::type replace(const StorageCommand& command, const std::string& data);
	virtual ResultCode::type append(const StorageCommand& command, const std::string& data);
	virtual ResultCode::type prepend(const StorageCommand& command, const std::string& data);
	virtual ResultCode::type cas(const StorageCommand& command, const std::string& data);

private:
	map_type map_;
	shared_mutex_type mutex_;
};

} // namespace mmc

#endif /* MMC_CACHE_HPP_INCLUDED */
