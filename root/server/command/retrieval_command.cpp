#include "command/retrieval_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"
#include <boost/bind.hpp>

namespace mmc {

RetrievalCommand::RetrievalCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
{}

RetrievalCommand::~RetrievalCommand()
{}

CommandBasePtr RetrievalCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::get)  type = CommandType::get;
	else if (name == constant::gets) type = CommandType::gets;

	RetrievalCommandPtr command;
	if (type != CommandType::none)
		command.reset(new RetrievalCommand(name, type));

	return command;
}

bool RetrievalCommand::parse(const arguments_type& args)
{
	set_keys(args);
	return true;
}

void RetrievalCommand::execute(ConnectionPtr connection)
{
}

} // namespace mmc
