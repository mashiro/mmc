#ifndef MMC_COMMAND_HPP_INCLUDED
#define MMC_COMMAND_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include <string>

namespace mmc {

MMC_ENUM_BEGIN(CommandType)
	none, 
	set, add, replace, append, prepend, cas,
MMC_ENUM_END()

MMC_FWD_DECL_CLASS(Command)
MMC_FWD_DECL_CLASS(Connection)

class Command : private boost::noncopyable
{
public:
	typedef std::vector<std::string> arguments_type;

public:
	Command(const std::string& name, CommandType::type type);

	static CommandPtr parse(const std::string& command);
	virtual bool parse(const arguments_type& args) = 0;
	virtual void execute(ConnectionPtr connection) = 0;

public:
	MMC_PROPERTY_DEF(std::string, name)
	MMC_PROPERTY_DEF(CommandType::type, type)
};

} // namespace mmc

#endif /* MMC_COMMAND_HPP_INCLUDED */
