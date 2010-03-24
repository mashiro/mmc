#include "cache.hpp"
#include "command/storage_command.hpp"
#include <boost/utility/value_init.hpp>

namespace mmc {

Cache::Cache()
	: cas_(new cache_cas_type(boost::initialized_value))
{}

Cache::~Cache()
{}

ResultCode::type Cache::set(const StorageCommand& command, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	CacheRecord& record = map_[command.get_key()];
	record.set_key(command.get_key());
	record.set_data(data);
	record.set_flags(command.get_flags());
	record.set_exptime(command.get_exptime());
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::add(const StorageCommand& command, const std::string& data)
{
	shared_lock_type slock(mutex_);
	iterator it = map_.find(command.get_key());
	if (it != map_.end())
	{
		return ResultCode::not_stored;
	}
	slock.unlock();

	unique_lock_type ulock(mutex_);
	CacheRecord& record = map_[command.get_key()];
	record.set_key(command.get_key());
	record.set_data(data);
	record.set_flags(command.get_flags());
	record.set_exptime(command.get_exptime());
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::replace(const StorageCommand& command, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(command.get_key());
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	CacheRecord& record = it->second;
	record.set_key(command.get_key());
	record.set_data(data);
	record.set_flags(command.get_flags());
	record.set_exptime(command.get_exptime());
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::append(const StorageCommand& command, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(command.get_key());
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	CacheRecord& record = it->second;
	record.set_key(command.get_key());
	record.set_data(record.get_data() + data);
	record.set_flags(command.get_flags());
	record.set_exptime(command.get_exptime());
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::prepend(const StorageCommand& command, const std::string& data)
{
	unique_lock_type ulock(mutex_);
	iterator it = map_.find(command.get_key());
	if (it == map_.end())
	{
		return ResultCode::not_stored;
	}

	CacheRecord& record = it->second;
	record.set_key(command.get_key());
	record.set_data(data + record.get_data());
	record.set_flags(command.get_flags());
	record.set_exptime(command.get_exptime());
	record.set_cas(get_next_cas());

	return ResultCode::stored;
}

ResultCode::type Cache::cas(const StorageCommand& command, const std::string& data)
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

} // namespace mmc
