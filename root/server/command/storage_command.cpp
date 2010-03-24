#include "command/storage_command.hpp"
#include "cache/cache_base.hpp"
#include "connection.hpp"
#include "lexical.hpp"
#include "constant.hpp"
#include <boost/bind.hpp>

namespace mmc {

StorageCommand::StorageCommand(const std::string& name, CommandType::type type) 
	: Command(name, type)
	, MMC_PROPERTY_NAME(key)()
	, MMC_PROPERTY_NAME(flags)(0)
	, MMC_PROPERTY_NAME(exptime)(0)
	, MMC_PROPERTY_NAME(bytes)(0)
	, MMC_PROPERTY_NAME(cas)(0)
	, MMC_PROPERTY_NAME(noreply)(false)
{}

StorageCommand::~StorageCommand()
{}

CommandPtr StorageCommand::parse(const std::string& name)
{
	CommandType::type type = CommandType::none;
	if      (name == constant::set)     type = CommandType::set;
	else if (name == constant::add)     type = CommandType::add;
	else if (name == constant::replace) type = CommandType::replace;
	else if (name == constant::append)  type = CommandType::append;
	else if (name == constant::prepend) type = CommandType::prepend;
	else if (name == constant::cas)     type = CommandType::cas;

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

void StorageCommand::execute(ConnectionPtr connection)
{
	connection->async_read(
		boost::bind(&StorageCommand::handle_datablock_read, shared_from_this(),
			connection,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void StorageCommand::handle_datablock_read(ConnectionPtr connection, const boost::system::error_code& error, std::size_t bytes_transferred)
{
	// datablock を読み込む
	std::string& buffer = connection->read_streambuf(bytes_transferred);
	if (buffer.size() != get_bytes())
	{
		// 長さが違う
		buffer = constant::client_error;
		buffer += " bad data chunk";
		buffer += constant::crlf;
	}
	else
	{
		// 処理
		ResultCode::type result = ResultCode::none;
		if (CacheBasePtr cache = connection->get_cache())
		{
			switch (get_type())
			{
				case CommandType::set:     result = cache->set(*this, buffer); break;
				case CommandType::add:     result = cache->add(*this, buffer); break;
				case CommandType::replace: result = cache->replace(*this, buffer); break;
				case CommandType::append:  result = cache->append(*this, buffer); break;
				case CommandType::prepend: result = cache->prepend(*this, buffer); break;
				case CommandType::cas:     result = cache->cas(*this, buffer); break;
			}

			buffer = result_code_to_string(result);
			buffer += constant::crlf;
		}
		else
		{
			buffer = constant::server_error;
			buffer += " cache missing";
			buffer += constant::crlf;
		}
	}

	// 結果を書き込む
	connection->async_write_result();
}

} // namespace mmc
