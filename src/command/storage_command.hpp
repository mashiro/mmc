#ifndef MMC_STORAGE_COMMAND_HPP_INCLUDED
#define MMC_STORAGE_COMMAND_HPP_INCLUDED

#include "command.hpp"

namespace mmc {

class StorageCommand : public Command
{
public:
	static CommandPtr parse(const std::string& name, const std::vector<std::string>& args);

public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(boost::uint32_t, flags)
	MMC_PROPERTY_DEF(boost::uint32_t, exptime)
	MMC_PROPERTY_DEF(boost::uint32_t, bytes)
	MMC_PROPERTY_DEF(bool, noreply)
};

class SetCommand
	: public StorageCommand
	, public boost::enable_shared_from_this<SetCommand>
{
public:
	virtual void execute(ConnectionPtr connection);
};

class AddCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<AddCommand>
{};

class ReplaceCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<ReplaceCommand>
{};

class AppendCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<AppendCommand>
{};

class PrependCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<PrependCommand>
{};

class CasCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<CasCommand>
{
public:
	MMC_PROPERTY_DEF(boost::uint64_t, cas_unique)
};

} // namespace mmc

#endif /* MMC_STORAGE_COMMAND_HPP_INCLUDED */
