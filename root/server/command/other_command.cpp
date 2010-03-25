#include "command/other_command.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"
#include <boost/bind.hpp>

namespace mmc {

OtherCommand::OtherCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
{}

CommandBasePtr OtherCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::command::version) type = CommandType::version;
	else if (name == constant::command::quit)    type = CommandType::quit;

	OtherCommandPtr command;
	if (type != CommandType::none)
		command.reset(new OtherCommand(name, type));

	return command;
}

bool OtherCommand::parse(const arguments_type& args)
{
	// 引数はとらない
	return args.size() == 0;
}

void OtherCommand::execute(ConnectionPtr connection)
{
	switch (get_type())
	{
		case CommandType::version:
			write_result(constant::result::version + constant::space + mmc_version);
			connection->async_write_result(to_buffers());
			break;

		case CommandType::quit:
			connection->shutdown();
			break;
	}
}

} // namespace mmc
