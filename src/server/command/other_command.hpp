#ifndef MMC_OTHER_COMMAND_HPP_INCLUDED
#define MMC_OTHER_COMMAND_HPP_INCLUDED

#include "command/command_base.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(OtherCommand)

class OtherCommand
	: public CommandBase
{
public:
	MMC_ENABLE_SHARED_THIS(OtherCommand)

	OtherCommand(const std::string& name, CommandType::type type);
	virtual ~OtherCommand();

	static CommandBasePtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute();
};

} // namespace mmc

#endif /* MMC_OTHER_COMMAND_HPP_INCLUDED */
