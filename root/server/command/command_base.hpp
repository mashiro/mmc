#ifndef MMC_COMMAND_BASE_HPP_INCLUDED
#define MMC_COMMAND_BASE_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <vector>

namespace mmc {

MMC_FWD_DECL_CLASS(CommandBase)
MMC_FWD_DECL_CLASS(Connection)

class CommandBase : private boost::noncopyable
{
public:
	typedef std::string argument_type;
	typedef std::vector<argument_type> arguments_type;

public:
	CommandBase(const std::string& name, CommandType::type type);
	virtual ~CommandBase();

	static CommandBasePtr parse(const std::string& command);
	virtual bool parse(const arguments_type& args) = 0;
	virtual void execute(ConnectionPtr connection) = 0;

public:
	void write_result(const std::string& result);
	void write_result(const std::string& result, const std::string& message);
	std::vector<boost::asio::const_buffer> to_buffers() const;

public:
	MMC_PROPERTY_DEF(std::string, name)
	MMC_PROPERTY_DEF(CommandType::type, type)
	MMC_PROPERTY_DEF(arguments_type, results)
};

} // namespace mmc

#endif /* MMC_COMMAND_BASE_HPP_INCLUDED */
