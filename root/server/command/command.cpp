#include "command/command.hpp"
#include "command/storage_command.hpp"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

namespace mmc {

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

	return cmd;
}

	/*
	if (cmd)
	{
		std::string key = args[0];
		boost::uint32_t flags = lexical(args[1]);
		boost::uint32_t exptime = lexical(args[2]);
		boost::uint32_t bytes = lexical(args[3]);
		bool noreply = (args.size() >= 5 && args[4] == "noreply");
	}
	else if (name == "cas")
	{
		if (args.size() < 5)
			return CommandPtr();

		std::string key = args[0];
		boost::uint32_t flags = lexical(args[1]);
		boost::uint32_t exptime = lexical(args[2]);
		boost::uint32_t bytes = lexical(args[3]);
		boost::uint64_t cas_unique = lexical(args[4]);
		bool noreply = (args.size() >= 6 && args[5] == "noreply");

		CasCommandPtr cmd(new CasCommand());
		cmd->set_key(key);
		cmd->set_flags(flags);
		cmd->set_exptime(exptime);
		cmd->set_bytes(bytes);
		cmd->set_noreply(noreply);
		*/

} // namespace mmc
