#ifndef MMC_STORAGE_COMMAND_HPP_INCLUDED
#define MMC_STORAGE_COMMAND_HPP_INCLUDED

#include "utility.hpp"
#include "asio_base.hpp"
#include "command/command.hpp"

namespace mmc {

MMC_ENUM_BEGIN(StorageType)
	none,
	set,
	add,
	replace,
	append,
	prepend,
	cas,
MMC_ENUM_END()

MMC_FWD_DECL_CLASS(StorageCommand)

class StorageCommand
	: public Command
	, public boost::enable_shared_from_this<StorageCommand>
{
public:
	StorageCommand(const std::string& name, StorageType::type type);

	static CommandPtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute(ConnectionPtr connection);

private:
	void handle_datablock_read(ConnectionPtr connection, const boost::system::error_code& error, std::size_t bytes_transferred);

public:
	MMC_PROPERTY_DEF(StorageType::type, type)
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(boost::uint32_t, flags)
	MMC_PROPERTY_DEF(boost::uint32_t, exptime)
	MMC_PROPERTY_DEF(boost::uint32_t, bytes)
	MMC_PROPERTY_DEF(boost::uint64_t, cas)
	MMC_PROPERTY_DEF(bool, noreply)
};

} // namespace mmc

#endif /* MMC_STORAGE_COMMAND_HPP_INCLUDED */
