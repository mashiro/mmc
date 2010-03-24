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
	if      (name == constant::get)  type = CommandType::get;
	else if (name == constant::gets) type = CommandType::gets;

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
		typedef keys_type::const_iterator iter_t;
		iter_t it = get_keys().begin();
		iter_t endit = get_keys().end();

		while (it != endit)
		{
			boost::optional<CacheRecord> record;
			switch (get_type())
			{
				case CommandType::get: record = cache->get(*it); break;
				case CommandType::gets: record = cache->gets(*it); break;
			}

			// ちゃんと boost::asio::buffer の配列にいれて渡す
			if (record)
			{
				connection->buffer() = record->get_data() + constant::crlf;
			}

			++it;
		}
	}

	connection->buffer() += constant::end;
	connection->buffer() += constant::crlf;

	connection->async_write_result();
}

} // namespace mmc
