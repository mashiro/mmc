#ifndef MMC_UTILITY_HPP_INCLUDED
#define MMC_UTILITY_HPP_INCLUDED

#include "config.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

// fwd
#define MMC_FWD_DECL_SHARED_PTR(name) typedef boost::shared_ptr<name> name##Ptr
#define MMC_FWD_DECL_WEAK_PTR(name) typedef boost::weak_ptr<name> name##WeakPtr
#define MMC_FWD_DECL_CLASS(name) \
	class name; \
	MMC_FWD_DECL_SHARED_PTR(name); \
	MMC_FWD_DECL_WEAK_PTR(name); \
/**/
#define MMC_FWD_DECL_STRUCT(name) \
	struct name; \
	MMC_FWD_DECL_SHARED_PTR(name); \
	MMC_FWD_DECL_WEAK_PTR(name); \
/**/

// property
#define MMC_PROPERTY_NAME(name) name##_
#define MMC_PROPERTY_DEF(type, name) \
	private: \
		type MMC_PROPERTY_NAME(name); \
		type& name() { return MMC_PROPERTY_NAME(name); } \
	public: \
		const type& get_##name() const { return MMC_PROPERTY_NAME(name); } \
		void set_##name(const type& value) { MMC_PROPERTY_NAME(name) = value; } \
/**/

namespace mmc {

const std::string& result_code_to_string(ResultCode::type result);

} // namespace mmc

#endif /* MMC_UTILITY_HPP_INCLUDED */
