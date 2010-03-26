#include "cache/cache.hpp"
#include "lexical.hpp"

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
	// TODO
	return ResultCode::not_stored;
}



ResultCode::type Cache::get(const std::string& key, CacheRecord& result) const
{
	shared_lock_type slock(mutex_);

	const_iterator it = map_.find(key);
	if (it == map_.end())
		return ResultCode::not_found;

	result = it->second;
	return ResultCode::ok;
}

ResultCode::type Cache::gets(const std::string& key, CacheRecord& result) const
{
	return get(key, result);
}



ResultCode::type Cache::delete_(const std::string& key, cache_exptime_type time)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(key);
	if (it == map_.end())
	{
		return ResultCode::not_found;
	}

	map_.erase(it);
	return ResultCode::deleted;
}



ResultCode::type Cache::incr(const std::string& key, cache_decimal_type value, cache_decimal_type& result)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(key);
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	cache_decimal_type num = 0;
	value_type& record = it->second;
	try
	{
		num = lexical(record.get_data());
		num += value;
	}
	catch (std::bad_cast&)
	{
		num = value;
	}

	record.set_data(lexical(num));
	record.set_cas(get_next_cas());
	result = num;

	return ResultCode::ok;
}

ResultCode::type Cache::decr(const std::string& key, cache_decimal_type value, cache_decimal_type& result)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(key);
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	cache_decimal_type num = 0;
	value_type& record = it->second;
	try
	{
		num = lexical(record.get_data());
		if (value > num) 
			num = 0;
		else
			num -= value;
	}
	catch (std::bad_cast&)
	{
		num = 0;
	}

	record.set_data(lexical(num));
	record.set_cas(get_next_cas());
	result = num;

	return ResultCode::ok;
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

} // namespace mmc
