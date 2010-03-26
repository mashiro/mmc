#include "command/incr_decr_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"

namespace mmc {

IncrDecrCommand::IncrDecrCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
	, MMC_PROPERTY_NAME(key)()
	, MMC_PROPERTY_NAME(value)(0)
	, MMC_PROPERTY_NAME(noreply)(false)
{}

IncrDecrCommand::~IncrDecrCommand()
{}

CommandBasePtr IncrDecrCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::command::incr) type = CommandType::incr;
	else if (name == constant::command::decr) type = CommandType::decr;

	if (type != CommandType::none)
		return IncrDecrCommandPtr(new IncrDecrCommand(name, type));
	else
		return IncrDecrCommandPtr();
}

bool IncrDecrCommand::parse(const arguments_type& args)
{
	try
	{
		if (args.size() < 2)
			return false;

		set_key(lexical(args[0]));
		set_value(lexical(args[1]));
		set_noreply(args.size() > 2 && args[2] == constant::noreply);
	}
	catch (std::bad_cast&)
	{
		return false;
	}

	return true;
}

void IncrDecrCommand::execute()
{
	ConnectionPtr connection = get_connection();

	// 処理
	if (CacheBasePtr cache = connection->get_cache())
	{
		ResultCode::type result = ResultCode::none;
		//result = cache->delete_(get_key(), get_time());

		add_result(result_code_to_string(result));
	}
	else
	{
		// キャッシュが存在しないエラー
		add_result(constant::result::server_error, "cache missing");
	}

	// 結果を書き込む
	if (get_noreply())
		connection->restart();
	else
		async_write_result();
}

} // namespace mmc
