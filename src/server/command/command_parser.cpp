#include "command/command_parser.hpp"
#include "command/command_base.hpp"
#include "command/storage_command.hpp"
#include "command/retrieval_command.hpp"
#include "command/deletion_command.hpp"
#include "command/incr_decr_command.hpp"
#include "command/other_command.hpp"
#include <boost/tokenizer.hpp>
#include <vector>

namespace mmc {

CommandParser::CommandParser()
{}

CommandBasePtr CommandParser::parse(const std::string& command)
{
	CommandBasePtr cmd;

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
	if (!cmd) cmd = StorageCommand::parse(name);
	if (!cmd) cmd = RetrievalCommand::parse(name);
	if (!cmd) cmd = DeletionCommand::parse(name);
	if (!cmd) cmd = IncrDecrCommand::parse(name);
	if (!cmd) cmd = OtherCommand::parse(name);
	if (cmd && cmd->parse(args))
		return cmd;
	else
		return CommandBasePtr();
}

} // namespace mmc
