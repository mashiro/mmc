#ifndef MMC_CONSTANT_HPP_INCLUDED
#define MMC_CONSTANT_HPP_INCLUDED

namespace mmc { namespace constant {

	// global
	const char* const crlf = "\r\n";
	const char* const noreply = "noreply";

	// storage
	const char* const set = "set";
	const char* const add = "add";
	const char* const replace = "replace";
	const char* const append = "append";
	const char* const prepend = "prepend";
	const char* const cas = "cas";

}} // namespace mmc::constant

#endif /* MMC_CONSTANT_HPP_INCLUDED */
