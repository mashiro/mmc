#ifndef MMC_COMMAND_HPP_INCLUDED
#define MMC_COMMAND_HPP_INCLUDED

#include "fwd_decl.hpp"
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
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
	static CommandPtr parse(const std::string& command);

public:
	virtual void execute(ConnectionPtr connection) = 0;
	MMC_PROPERTY_DEF(std::string, name)
};


template <typename Source>
class lexical_t
{
public:
	lexical_t(const Source& source)
		: source_(source)
	{}

	template <typename Target>
	operator Target() const
	{
		return boost::lexical_cast<Target>(source_);
	}

private:
	const Source& source_;
};

template <typename Source>
lexical_t<Source> lexical(const Source& source)
{
	return lexical_t<Source>(source);
}

} // namespace mmc

#endif /* MMC_COMMAND_HPP_INCLUDED */
