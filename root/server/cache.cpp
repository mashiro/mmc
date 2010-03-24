#include "cache.hpp"
#include "command/storage_command.hpp"

namespace mmc {

Cache::Cache()
{}

bool Cache::set(const StorageCommand& command, const std::string& data)
{
	CacheRecord record;
	record.set_data(data);
	record.set_flags(command.get_flags());
	record.set_exptime(command.get_exptime());
	record.set_cas(command.get_cas());
	map_[command.get_key()] = record;
	return true;
}

} // namespace mmc
