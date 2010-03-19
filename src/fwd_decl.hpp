#ifndef MMC_FWD_HPP_INCLUDED
#define MMC_FWD_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#define MMC_FWD_DECL_SHARED_PTR(name) \
	typedef boost::shared_ptr<name> name##Ptr; \
/**/

#define MMC_FWD_DECL_CLASS(name) \
	class name; \
	MMC_FWD_DECL_SHARED_PTR(name) \
/**/

#define MMC_FWD_DECL_STRUCT(name) \
	struct name; \
	MMC_FWD_DECL_SHARED_PTR(name) \
/**/

#endif /* MMC_FWD_HPP_INCLUDED */
