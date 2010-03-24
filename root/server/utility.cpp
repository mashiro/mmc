#include "utility.hpp"

namespace mmc {

const char* result_code_to_string(ResultCode::type result)
{
	switch (result)
	{
		case ResultCode::stored:     return "STORED";
		case ResultCode::not_stored: return "NOT_STORED";
		case ResultCode::exists:     return "EXISTS";
		case ResultCode::not_found:  return "NOT_FOUND";
		case ResultCode::deleted:    return "DELETED";
		default: return 0;
	}
}

} // namespace mmc
