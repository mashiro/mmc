#include "command/storage/storage_command.hpp"
#include "command/storage/set_command.hpp"
#include "connection.hpp"
#include "lexical.hpp"

namespace mmc {

CommandPtr StorageCommand::parse(const std::string& name, const std::vector<std::string>& args)
{
	StorageCommandPtr cmd;

	if (name == "set")
		cmd = SetCommandPtr(new SetCommand());

	/*
	if (name == "set")
		cmd = SetCommandPtr(new SetCommand());
	else if (name == "add")
		cmd = AddCommandPtr(new AddCommand());
	else if (name == "replace")
		cmd = ReplaceCommandPtr(new ReplaceCommand());
	else if (name == "append")
		cmd = AppendCommandPtr(new AppendCommand());
	else if (name == "prepned")
		cmd = PrependCommandPtr(new PrependCommand());
	else if (name == "cas")
		cmd = CasCommandPtr(new CasCommand());
	*/

	if (cmd && cmd->parse(args))
		return cmd;

	return CommandPtr();
}

bool StorageCommand::parse(const std::vector<std::string>& args)
{
	if (args.size() < 4)
		return false;

	try
	{
		set_key(lexical(args[0]));
		set_flags(lexical(args[1]));
		set_exptime(lexical(args[2]));
		set_bytes(lexical(args[3]));
		set_noreply(args.size() > 4 && args[4] == "noreply");
	}
	catch (std::bad_cast&)
	{
		return false;
	}

	return true;

	/*
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
}

} // namespace mmc
