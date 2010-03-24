#ifndef MMC_RETRIEVAL_COMMAND_HPP_INCLUDED
#define MMC_RETRIEVAL_COMMAND_HPP_INCLUDED

#include "command/command.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(RetrievalCommand)

class RetrievalCommand
	: public Command
	, public boost::enable_shared_from_this<RetrievalCommand>
{
public:
	typedef arguments_type keys_type;

public:
	RetrievalCommand(const std::string& name, CommandType::type type);
	virtual ~RetrievalCommand();

	static CommandPtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute(ConnectionPtr connection);

public:
	MMC_PROPERTY_DEF(keys_type, keys)
};

} // namespace mmc

#endif /* MMC_RETRIEVAL_COMMAND_HPP_INCLUDED */
