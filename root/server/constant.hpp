#ifndef MMC_CONSTANT_HPP_INCLUDED
#define MMC_CONSTANT_HPP_INCLUDED

#include <string>

namespace mmc { namespace constant {

	// global
	const std::string crlf    = "\r\n";
	const std::string space   = " ";
	const std::string noreply = "noreply";

	// storage
	const std::string set     = "set";
	const std::string add     = "add";
	const std::string replace = "replace";
	const std::string append  = "append";
	const std::string prepend = "prepend";
	const std::string cas     = "cas";

	// retrieval
	const std::string get     = "get";
	const std::string gets    = "gets";

	// other
	const std::string version = "version";
	const std::string quit    = "quit";

	// result
	const std::string error        = "ERROR";
	const std::string client_error = "CLIENT_ERROR";
	const std::string server_error = "SERVER_ERROR";
	const std::string stored       = "STORED";
	const std::string not_stored   = "NOT_STORED";
	const std::string exists       = "EXISTS";
	const std::string not_found    = "NOT_FOUND";
	const std::string end          = "END";

	// message

}} // namespace mmc::constant

#endif /* MMC_CONSTANT_HPP_INCLUDED */
