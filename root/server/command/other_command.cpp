#include "command/other_command.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"
#include <boost/bind.hpp>

namespace mmc {

OtherCommand::OtherCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
{}

OtherCommand::~OtherCommand()
{}

CommandBasePtr OtherCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::command::version) type = CommandType::version;
	else if (name == constant::command::quit)    type = CommandType::quit;

	if (type != CommandType::none)
		return OtherCommandPtr(new OtherCommand(name, type));
	else
		return OtherCommandPtr();
}

bool OtherCommand::parse(const arguments_type& args)
{
	// 引数はとらない
	return args.size() == 0;
}

void OtherCommand::execute()
{
	switch (get_type())
	{
		case CommandType::version:
			add_result(constant::result::version + constant::space + mmc_version);
			async_write_result();
			break;

		case CommandType::quit:
			get_connection()->shutdown();
			break;
	}
}

} // namespace mmc
