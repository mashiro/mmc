#ifndef MMC_INCR_DECR_COMMAND_HPP_INCLUDED
#define MMC_INCR_DECR_COMMAND_HPP_INCLUDED

#include "command/command_base.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(IncrDecrCommand)

class IncrDecrCommand
	: public CommandBase
{
public:
	MMC_ENABLE_SHARED_THIS(IncrDecrCommand)

	IncrDecrCommand(const std::string& name, CommandType::type type);
	virtual ~IncrDecrCommand();

	static CommandBasePtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute();

public:
	MMC_PROPERTY_DEF(std::string, key)
	MMC_PROPERTY_DEF(cache_decimal_type, value)
	MMC_PROPERTY_DEF(bool, noreply)
};

} // namespace mmc

#endif /* MMC_INCR_DECR_COMMAND_HPP_INCLUDED */
