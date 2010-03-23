#include "command/storage_command.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"

namespace mmc {

StorageCommand::StorageCommand(const std::string& name, StorageType::type type) 
	: Command(name)
	, MMC_PROPERTY_NAME(type)(type)
	, MMC_PROPERTY_NAME(key)()
	, MMC_PROPERTY_NAME(flags)(0)
	, MMC_PROPERTY_NAME(exptime)(0)
	, MMC_PROPERTY_NAME(bytes)(0)
	, MMC_PROPERTY_NAME(cas)(0)
	, MMC_PROPERTY_NAME(noreply)(false)
{}

CommandPtr StorageCommand::parse(const std::string& name)
{
	StorageType::type type = StorageType::none;
	if      (name == constant::set)     type = StorageType::set;
	else if (name == constant::add)     type = StorageType::add;
	else if (name == constant::replace) type = StorageType::replace;
	else if (name == constant::append)  type = StorageType::append;
	else if (name == constant::prepend) type = StorageType::prepend;
	else if (name == constant::cas)     type = StorageType::cas;

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
			set_cas(lexical(args[4]));
			set_noreply(args.size() > 5 && args[5] == constant::noreply);
		}
		else
		{
			if (args.size() < 4)
				return false;

			set_key(lexical(args[0]));
			set_flags(lexical(args[1]));
			set_exptime(lexical(args[2]));
			set_bytes(lexical(args[3]));
			set_noreply(args.size() > 4 && args[4] == constant::noreply);
		}
	}
	catch (std::bad_cast&)
	{
		return false;
	}

	return true;
}

void StorageCommand::execute(ConnectionPtr connection)
{
}

} // namespace mmc
