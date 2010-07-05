#ifndef MMC_COMMAND_PARSER_HPP_INCLUDED
#define MMC_COMMAND_PARSER_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(CommandBase)

class CommandParser
{
private:
	CommandParser();

public:
	static CommandBasePtr parse(const std::string& command);
};

} // namespace mmc

#endif /* MMC_COMMAND_PARSER_HPP_INCLUDED */
