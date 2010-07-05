#ifndef MMC_DELETION_COMMAND_HPP_INCLUDED
#define MMC_DELETION_COMMAND_HPP_INCLUDED

#include "command/command_base.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(DeletionCommand)

class DeletionCommand
	: public CommandBase
{
public:
	MMC_ENABLE_SHARED_THIS(DeletionCommand)

	DeletionCommand(const std::string& name, CommandType::type type);
	virtual ~DeletionCommand();

	static CommandBasePtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute();

public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(cache_exptime_type, time)
	MMC_PROPERTY_DEF(bool, noreply)
};

} // namespace mmc

#endif /* MMC_DELETION_COMMAND_HPP_INCLUDED */
