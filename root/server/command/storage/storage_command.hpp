#ifndef MMC_STORAGE_COMMAND_HPP_INCLUDED
#define MMC_STORAGE_COMMAND_HPP_INCLUDED

#include "command/command.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(StorageCommand)
/*
MMC_FWD_DECL_CLASS(SetCommand)
MMC_FWD_DECL_CLASS(AddCommand)
MMC_FWD_DECL_CLASS(ReplaceCommand)
MMC_FWD_DECL_CLASS(AppendCommand)
MMC_FWD_DECL_CLASS(PrependCommand)
MMC_FWD_DECL_CLASS(CasCommand)
*/

class StorageCommand : public Command
{
public:
	static CommandPtr parse(const std::string& name, const std::vector<std::string>& args);
	virtual bool parse(const std::vector<std::string>& args);

public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(boost::uint32_t, flags)
	MMC_PROPERTY_DEF(boost::uint32_t, exptime)
	MMC_PROPERTY_DEF(boost::uint32_t, bytes)
	MMC_PROPERTY_DEF(bool, noreply)
};

/*
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
{
public:
	virtual void execute(ConnectionPtr connection);
};

class ReplaceCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<ReplaceCommand>
{
public:
	virtual void execute(ConnectionPtr connection);
};

class AppendCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<AppendCommand>
{
public:
	virtual void execute(ConnectionPtr connection);
};

class PrependCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<PrependCommand>
{
public:
	virtual void execute(ConnectionPtr connection);
};

class CasCommand
	: public StorageCommand 
	, public boost::enable_shared_from_this<CasCommand>
{
public:
	MMC_PROPERTY_DEF(boost::uint64_t, cas_unique)
};
*/

} // namespace mmc

#endif /* MMC_STORAGE_COMMAND_HPP_INCLUDED */
