#ifndef MMC_RETRIEVAL_COMMAND_HPP_INCLUDED
#define MMC_RETRIEVAL_COMMAND_HPP_INCLUDED

#include "command/command_base.hpp"

namespace mmc {

MMC_FWD_DECL_CLASS(RetrievalCommand)

class RetrievalCommand
	: public CommandBase
{
public:
	typedef arguments_type keys_type;

public:
	MMC_ENABLE_SHARED_THIS(RetrievalCommand)

	RetrievalCommand(const std::string& name, CommandType::type type);
	virtual ~RetrievalCommand();

	static CommandBasePtr parse(const std::string& name);
	virtual bool parse(const arguments_type& args);
	virtual void execute();

public:
	MMC_PROPERTY_DEF(keys_type, keys)
};

} // namespace mmc

#endif /* MMC_RETRIEVAL_COMMAND_HPP_INCLUDED */
