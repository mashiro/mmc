#ifndef MMC_COMMAND_BASE_HPP_INCLUDED
#define MMC_COMMAND_BASE_HPP_INCLUDED

#include "config.hpp"
#include "utility.hpp"
#include "shared_object.hpp"
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace mmc {

MMC_FWD_DECL_CLASS(CommandBase)
MMC_FWD_DECL_CLASS(Connection)

class CommandBase
	: public SharedObject
	, private boost::noncopyable
{
public:
	typedef std::string argument_type;
	typedef std::vector<argument_type> arguments_type;

public:
	MMC_ENABLE_SHARED_THIS(CommandBase)

	CommandBase(const std::string& name, CommandType::type type);
	virtual ~CommandBase();

	static CommandBasePtr parse(const std::string& command);
	virtual bool parse(const arguments_type& args) = 0;
	virtual void execute() = 0;

protected:
	void add_result(const std::string& result);
	void add_result(const std::string& result, const std::string& message);
	void async_write_result();

private:
	std::vector<boost::asio::const_buffer> to_buffers() const;
	void handle_write_result(const boost::system::error_code& error);

public:
	MMC_PROPERTY_DEF(ConnectionPtr, connection)
	MMC_PROPERTY_DEF(std::string, name)
	MMC_PROPERTY_DEF(CommandType::type, type)
	MMC_PROPERTY_DEF(arguments_type, results)
};

} // namespace mmc

#endif /* MMC_COMMAND_BASE_HPP_INCLUDED */
