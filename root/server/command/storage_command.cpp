#include "command/storage_command.hpp"
#include "connection.hpp"
#include "lexical.hpp"

namespace mmc {

StorageCommand::StorageCommand(const std::string& name, StorageType::type type) 
	: Command(name)
{
	set_type(type);
}

CommandPtr StorageCommand::parse(const std::string& name)
{
	StorageType::type type = StorageType::none;
	if      (name == "set")     type = StorageType::set;
	else if (name == "add")     type = StorageType::add;
	else if (name == "replace") type = StorageType::replace;
	else if (name == "append")  type = StorageType::append;
	else if (name == "prepned") type = StorageType::prepend;
	else if (name == "cas")     type = StorageType::cas;

	StorageCommandPtr command;
	if (type != StorageType::none)
		command.reset(new StorageCommand(name, type));

	return command;
}

bool StorageCommand::parse(const std::vector<std::string>& args)
{
	try
	{
		if (get_type() == StorageType::cas)
		{
			if (args.size() < 5)
				return false;

			set_key(lexical(args[0]));
			set_flags(lexical(args[1]));
			set_exptime(lexical(args[2]));
			set_bytes(lexical(args[3]));
			set_bytes(lexical(args[3]));
			set_noreply(args.size() > 4 && args[4] == "noreply");
		}
		else
		{
			if (args.size() < 4)
				return false;

			set_key(lexical(args[0]));
			set_flags(lexical(args[1]));
			set_exptime(lexical(args[2]));
			set_bytes(lexical(args[3]));
			set_cas(lexical(args[4]));
			set_noreply(args.size() > 5 && args[5] == "noreply");
		}
	}
	catch (std::bad_cast&)
	{
		// パース失敗
		return false;
	}

	return true;
}

} // namespace mmc
