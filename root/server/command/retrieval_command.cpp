#include "command/retrieval_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"
#include <boost/bind.hpp>

namespace mmc {

RetrievalCommand::RetrievalCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
{}

RetrievalCommand::~RetrievalCommand()
{}

CommandBasePtr RetrievalCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::command::get)  type = CommandType::get;
	else if (name == constant::command::gets) type = CommandType::gets;

	RetrievalCommandPtr command;
	if (type != CommandType::none)
		command.reset(new RetrievalCommand(name, type));

	return command;
}

bool RetrievalCommand::parse(const arguments_type& args)
{
	set_keys(args);
	return true;
}

void RetrievalCommand::execute(ConnectionPtr connection)
{
	// 処理
	ResultCode::type result = ResultCode::none;
	if (CacheBasePtr cache = connection->get_cache())
	{
		for (std::size_t i = 0; i < get_keys().size(); ++i)
		{
			const argument_type& key = get_keys().at(i);

			boost::optional<CacheRecord> record;
			switch (get_type())
			{
				case CommandType::get: record = cache->get(key); break;
				case CommandType::gets: record = cache->gets(key); break;
			}

			if (record)
			{
				std::string header = key
					+ constant::space + to_string(record->get_flags())
					+ constant::space + to_string(record->get_data().size())
					;

				if (get_type() == CommandType::gets)
					header += constant::space + to_string(record->get_cas());

				write_result(constant::result::value, header);
				write_result(record->get_data());
			}
		}
	}

	write_result(constant::result::end);
	connection->async_write_result(to_buffers());
}

} // namespace mmc
