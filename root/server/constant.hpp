#ifndef MMC_CONSTANT_HPP_INCLUDED
#define MMC_CONSTANT_HPP_INCLUDED

namespace mmc { namespace constant {

	// global
	const char* const crlf    = "\r\n";
	const char* const space   = " ";
	const char* const noreply = "noreply";

	// storage
	const char* const set     = "set";
	const char* const add     = "add";
	const char* const replace = "replace";
	const char* const append  = "append";
	const char* const prepend = "prepend";
	const char* const cas     = "cas";

	// retrieval
	const char* const get     = "get";
	const char* const gets    = "gets";

	// other
	const char* const version = "version";
	const char* const quit    = "quit";

	// result
	const char* const error        = "ERROR";
	const char* const client_error = "CLIENT_ERROR";
	const char* const server_error = "SERVER_ERROR";
	const char* const stored       = "STORED";
	const char* const not_stored   = "NOT_STORED";
	const char* const exists       = "EXISTS";
	const char* const not_found    = "NOT_FOUND";
	const char* const end          = "END";

	// message

}} // namespace mmc::constant

#endif /* MMC_CONSTANT_HPP_INCLUDED */
