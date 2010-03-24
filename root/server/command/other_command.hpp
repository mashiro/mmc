#ifndef MMC_OTHER_COMMAND_HPP_INCLUDED
#define MMC_OTHER_COMMAND_HPP_INCLUDED

#include "command/command_base.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(OtherCommand)

class OtherCommand
	: public CommandBase
	, public boost::enable_shared_from_this<OtherCommand>
{
public:
	OtherCommand(const std::string& name, CommandType::type type);

	static CommandBasePtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute(ConnectionPtr connection);
};

} // namespace mmc

#endif /* MMC_OTHER_COMMAND_HPP_INCLUDED */
