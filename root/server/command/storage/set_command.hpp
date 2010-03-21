#ifndef MMC_SET_COMMAND_HPP_INCLUDED
#define MMC_SET_COMMAND_HPP_INCLUDED

#include "command/storage/storage_command.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(SetCommand)

class SetCommand
	: public StorageCommand
	, public boost::enable_shared_from_this<SetCommand>
{
public:
	virtual void execute(ConnectionPtr connection);
};

} // namespace mmc

#endif /* MMC_SET_COMMAND_HPP_INCLUDED */
