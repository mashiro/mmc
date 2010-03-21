#ifndef MMC_COMMAND_HPP_INCLUDED
#define MMC_COMMAND_HPP_INCLUDED

#include "fwd_decl.hpp"
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include <string>

namespace mmc {

#define MMC_PROPERTY_DEF(type, name) \
	private: \
		type name##_; \
	public: \
		const type& get_##name() const { return name##_; } \
		void set_##name(const type& value) { name##_ = value; } \
/**/

MMC_FWD_DECL_CLASS(Command)
MMC_FWD_DECL_CLASS(Connection)

class Command : private boost::noncopyable
{
public:
	Command(const std::string& name);

	static CommandPtr parse(const std::string& command);

	virtual bool parse(const std::vector<std::string>& args) = 0;
	virtual void execute(ConnectionPtr connection) = 0;

public:
	MMC_PROPERTY_DEF(std::string, name)
};

} // namespace mmc

#endif /* MMC_COMMAND_HPP_INCLUDED */
