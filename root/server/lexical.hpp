#ifndef MMC_LEXICAL_HPP_INCLUDED
#define MMC_LEXICAL_HPP_INCLUDED

#include <boost/lexical_cast.hpp>

namespace mmc {

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
inline lexical_t<Source> lexical(const Source& source)
{
	return lexical_t<Source>(source);
}

template <typename Source>
inline std::string to_string(const Source& source)
{
	return lexical(source);
}

} // namespace mmc

#endif /* MMC_LEXICAL_HPP_INCLUDED */
