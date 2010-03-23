#ifndef MMC_OTHER_COMMAND_HPP_INCLUDED
#define MMC_OTHER_COMMAND_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"
#include "asio_base.hpp"
#include "command/command.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(OtherCommand)

class OtherCommand
	: public Command
	, public boost::enable_shared_from_this<OtherCommand>
{
public:
	OtherCommand(const std::string& name, CommandType::type type);

	static CommandPtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute(ConnectionPtr connection);
};

} // namespace mmc

#endif /* MMC_OTHER_COMMAND_HPP_INCLUDED */
