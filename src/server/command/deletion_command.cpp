#include "command/deletion_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"

namespace mmc {

DeletionCommand::DeletionCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
	, MMC_PROPERTY_NAME(key)()
	, MMC_PROPERTY_NAME(time)(0)
	, MMC_PROPERTY_NAME(noreply)(false)
{}

DeletionCommand::~DeletionCommand()
{}

CommandBasePtr DeletionCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if (name == constant::command::delete_) type = CommandType::delete_;

	if (type != CommandType::none)
		return DeletionCommandPtr(new DeletionCommand(name, type));
	else
		return DeletionCommandPtr();
}

bool DeletionCommand::parse(const arguments_type& args)
{
	try
	{
		if (args.size() < 1)
			return false;

		set_key(lexical(args[0]));
		if (args.size() > 1)
		{
			if (args.size() > 2)
			{
				set_time(lexical(args[1]));
				set_noreply(args.size() > 2 && args[2] == constant::noreply);
			}
			else
			{
				set_noreply(args.size() > 1 && args[1] == constant::noreply);
			}
		}
	}
	catch (std::bad_cast&)
	{
		return false;
	}

	return true;
}

void DeletionCommand::execute()
{
	ConnectionPtr connection = get_connection();

	// 処理
	if (CacheBasePtr cache = connection->get_cache())
	{
		ResultCode::type result = ResultCode::none;
		result = cache->delete_(get_key(), get_time());

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
