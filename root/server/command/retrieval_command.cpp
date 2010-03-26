#include "command/retrieval_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"

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

	if (type != CommandType::none)
		return RetrievalCommandPtr(new RetrievalCommand(name, type));
	else
		return RetrievalCommandPtr();
}

bool RetrievalCommand::parse(const arguments_type& args)
{
	set_keys(args);
	return true;
}

void RetrievalCommand::execute()
{
	// 処理
	ResultCode::type result = ResultCode::none;
	if (CacheBasePtr cache = get_connection()->get_cache())
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

				add_result(constant::result::value, header);
				add_result(record->get_data());
			}
		}
	}

	add_result(constant::result::end);
	async_write_result();
}

} // namespace mmc
