#include "command/storage_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"
#include <boost/bind.hpp>

namespace mmc {

StorageCommand::StorageCommand(const std::string& name, CommandType::type type) 
	: CommandBase(name, type)
	, MMC_PROPERTY_NAME(key)()
	, MMC_PROPERTY_NAME(flags)(0)
	, MMC_PROPERTY_NAME(exptime)(0)
	, MMC_PROPERTY_NAME(bytes)(0)
	, MMC_PROPERTY_NAME(cas)(0)
	, MMC_PROPERTY_NAME(noreply)(false)
{}

StorageCommand::~StorageCommand()
{}

CommandBasePtr StorageCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::command::set)     type = CommandType::set;
	else if (name == constant::command::add)     type = CommandType::add;
	else if (name == constant::command::replace) type = CommandType::replace;
	else if (name == constant::command::append)  type = CommandType::append;
	else if (name == constant::command::prepend) type = CommandType::prepend;
	else if (name == constant::command::cas)     type = CommandType::cas;

	StorageCommandPtr command;
	if (type != CommandType::none)
		command.reset(new StorageCommand(name, type));

	return command;
}

bool StorageCommand::parse(const arguments_type& args)
{
	try
	{
		if (get_type() == CommandType::cas)
		{
			if (args.size() < 5)
				return false;

			set_key(lexical(args[0]));
			set_flags(lexical(args[1]));
			set_exptime(lexical(args[2]));
			set_bytes(lexical(args[3]));
			set_cas(lexical(args[4]));
			set_noreply(args.size() > 5 && args[5] == constant::noreply);
		}
		else
		{
			if (args.size() < 4)
				return false;

			set_key(lexical(args[0]));
			set_flags(lexical(args[1]));
			set_exptime(lexical(args[2]));
			set_bytes(lexical(args[3]));
			set_noreply(args.size() > 4 && args[4] == constant::noreply);
		}
	}
	catch (std::bad_cast&)
	{
		return false;
	}

	return true;
}

void StorageCommand::execute()
{
	get_connection()->async_read(
		boost::bind(&StorageCommand::handle_datablock_read, shared_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void StorageCommand::handle_datablock_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	// datablock を読み込む
	std::size_t length = get_connection()->read_streambuf(bytes_transferred);
	if (length != get_bytes())
	{
		// 長さが違うエラー
		add_result(constant::result::client_error, "bad data chunk");
	}
	else
	{
		// 処理
		ResultCode::type result = ResultCode::none;
		if (CacheBasePtr cache = get_connection()->get_cache())
		{
			const std::string& buffer = get_connection()->get_buffer();
			switch (get_type())
			{
				case CommandType::set:     result = cache->set(get_key(), get_flags(), get_exptime(), buffer); break;
				case CommandType::add:     result = cache->add(get_key(), get_flags(), get_exptime(), buffer); break;
				case CommandType::replace: result = cache->replace(get_key(), get_flags(), get_exptime(), buffer); break;
				case CommandType::append:  result = cache->append(get_key(), get_flags(), get_exptime(), buffer); break;
				case CommandType::prepend: result = cache->prepend(get_key(), get_flags(), get_exptime(), buffer); break;
				case CommandType::cas:     result = cache->cas(get_key(), get_flags(), get_exptime(), get_cas(), buffer); break;
			}

			add_result(result_code_to_string(result));
		}
		else
		{
			// キャッシュが存在しないエラー
			add_result(constant::result::server_error, "cache missing");
		}
	}

	// 結果を書き込む
	async_write_result();
}

} // namespace mmc
