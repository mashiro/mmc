#ifndef MMC_STORAGE_COMMAND_HPP_INCLUDED
#define MMC_STORAGE_COMMAND_HPP_INCLUDED

#include "command/command_base.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(StorageCommand)

class StorageCommand
	: public CommandBase
{
public:
	MMC_ENABLE_SHARED_THIS(StorageCommand)

	StorageCommand(const std::string& name, CommandType::type type);
	virtual ~StorageCommand();

	static CommandBasePtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute();

private:
	void handle_datablock_read(const boost::system::error_code& error, std::size_t bytes_transferred);

public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(cache_flags_type, flags)
	MMC_PROPERTY_DEF(cache_exptime_type, exptime)
	MMC_PROPERTY_DEF(cache_bytes_type, bytes)
	MMC_PROPERTY_DEF(cache_cas_type, cas)
	MMC_PROPERTY_DEF(bool, noreply)
};

} // namespace mmc

#endif /* MMC_STORAGE_COMMAND_HPP_INCLUDED */
