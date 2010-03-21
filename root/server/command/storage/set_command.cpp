#include "command/storage/set_command.hpp"
#include "connection.hpp"

namespace mmc {

SetCommand::SetCommand(const std::string& name)
	: StorageCommand(name)
{}

void SetCommand::execute(ConnectionPtr connection)
{
}

} // namespace mmc
