#include "cache/cache.hpp"

namespace mmc {

Cache::Cache()
	: cas_(new cache_cas_type(0))
{}

Cache::~Cache()
{}

ResultCode::type Cache::set(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	value_type& record = map_[key];
	record.set_data(data);
	record.set_flags(flags);
	record.set_exptime(exptime);
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::add(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data)
{
	shared_lock_type slock(mutex_);
	iterator it = map_.find(key);
	if (it != map_.end())
	{
		return ResultCode::not_stored;
	}
	slock.unlock();

	unique_lock_type ulock(mutex_);
	value_type& record = map_[key];
	record.set_data(data);
	record.set_flags(flags);
	record.set_exptime(exptime);
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::replace(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(key);
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	value_type& record = it->second;
	record.set_data(data);
	record.set_flags(flags);
	record.set_exptime(exptime);
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::append(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(key);
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	value_type& record = it->second;
	record.set_data(record.get_data() + data);
	record.set_flags(flags);
	record.set_exptime(exptime);
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::prepend(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(key);
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	value_type& record = it->second;
	record.set_data(data + record.get_data());
	record.set_flags(flags);
	record.set_exptime(exptime);
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::cas(const std::string& key, cache_flags_type flags, cache_exptime_type exptime, cache_cas_type cas, const std::string& data)
{
	return ResultCode::stored;
}

cache_cas_type Cache::get_next_cas()
{
	atomic_cas_type p1 = boost::atomic_load(&cas_);
	while (1)
	{
		atomic_cas_type p2(new cache_cas_type(*p1));
		++(*p2);
		if (boost::atomic_compare_exchange(&cas_, &p1, p2)) break;
	}
	return *cas_;
}


boost::optional<CacheRecord> Cache::get(const std::string& key) const
{
	shared_lock_type slock(mutex_);

	const_iterator it = map_.find(key);
	if (it == map_.end())
	{
		return boost::optional<CacheRecord>();
	}

	return boost::optional<CacheRecord>(it->second);
}

boost::optional<CacheRecord> Cache::gets(const std::string& key) const
{
	return get(key);
}

} // namespace mmc
