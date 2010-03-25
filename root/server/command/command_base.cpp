#include "command/command_base.hpp"
#include "command/storage_command.hpp"
#include "command/retrieval_command.hpp"
#include "command/other_command.hpp"
#include "constant.hpp"
#include <boost/tokenizer.hpp>

namespace mmc {

CommandBase::CommandBase(const std::string& name, CommandType::type type)
	: MMC_PROPERTY_NAME(name)(name)
	, MMC_PROPERTY_NAME(type)(type)
{}

CommandBase::~CommandBase()
{}

CommandBasePtr CommandBase::parse(const std::string& command)
{
	CommandBasePtr cmd;

	if (command.empty())
		return cmd;

	typedef boost::char_separator<char> separator_t;
	typedef boost::tokenizer<separator_t> tokenizer_t;
	separator_t separator(" ");
	tokenizer_t tokenizer(command, separator);

	bool first = true;
	std::string name;
	std::vector<std::string> args;

	typedef tokenizer_t::iterator iter_t;
	for (iter_t it = tokenizer.begin(), endit = tokenizer.end(); it != endit; ++it)
	{
		if (first)
		{
			first = false;
			name = *it;
		}
		else
		{
			args.push_back(*it);
		}
	}

	// parse
	if (!cmd) cmd = StorageCommand::parse(name);
	if (!cmd) cmd = RetrievalCommand::parse(name);
	if (!cmd) cmd = OtherCommand::parse(name);
	if (cmd && cmd->parse(args))
		return cmd;
	else
		return CommandBasePtr();
}

void CommandBase::write_result(const std::string& result)
{
	std::string s = result + constant::crlf;
	MMC_PROPERTY_NAME(results).push_back(s);
}

void CommandBase::write_result(const std::string& result, const std::string& message)
{
	std::string s = result + constant::space + message + constant::crlf;
	MMC_PROPERTY_NAME(results).push_back(s);
}

std::vector<boost::asio::const_buffer> CommandBase::to_buffers() const
{
	std::vector<boost::asio::const_buffer> buffers;
	for (std::size_t i = 0; i < MMC_PROPERTY_NAME(results).size(); ++i)
	{
		const std::string& result = MMC_PROPERTY_NAME(results)[i];
		buffers.push_back(boost::asio::buffer(result));
	}

	return buffers;
}

} // namespace mmc
