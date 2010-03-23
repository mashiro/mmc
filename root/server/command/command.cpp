#include "command/command.hpp"
#include "command/storage_command.hpp"
#include "command/other_command.hpp"
#include <boost/tokenizer.hpp>

namespace mmc {

Command::Command(const std::string& name, CommandType::type type)
	: MMC_PROPERTY_NAME(name)(name)
	, MMC_PROPERTY_NAME(type)(type)
{}

CommandPtr Command::parse(const std::string& command)
{
	CommandPtr cmd;

	if (command.empty())
		return cmd;

	typedef boost::char_separator<char> separator_t;
	typedef boost::tokenizer<separator_t> tokenizer_t;
	separator_t separator(" ");
	tokenizer_t tokenizer(command, separator);

	bool first = true;
	std::string name;
	std::vector<std::string> args;

	typedef tokenizer_t::iterator iter_t;
	for (iter_t it = tokenizer.begin(), endit = tokenizer.end(); it != endit; ++it)
	{
		if (first)
		{
			first = false;
			name = *it;
		}
		else
		{
			args.push_back(*it);
		}
	}

	// parse
	if      (!cmd) cmd = StorageCommand::parse(name);
	else if (!cmd) cmd = OtherCommand::parse(name);
	else if (!cmd) cmd = StorageCommand::parse(name);
	else if (!cmd) cmd = StorageCommand::parse(name);

	if (cmd && cmd->parse(args))
		return cmd;
	else
		return CommandPtr();
}

} // namespace mmc
