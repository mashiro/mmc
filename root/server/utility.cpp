#include "utility.hpp"

namespace mmc {

const std::string& result_code_to_string(ResultCode::type result)
{
	switch (result)
	{
		case ResultCode::stored:     return constant::result::stored;
		case ResultCode::not_stored: return constant::result::not_stored;
		case ResultCode::exists:     return constant::result::exists;
		case ResultCode::not_found:  return constant::result::not_found;
		case ResultCode::deleted:    return constant::result::deleted;
		default: return constant::empty;
	}
}

} // namespace mmc
