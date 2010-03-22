#ifndef MMC_UTILITY_HPP_INCLUDED
#define MMC_UTILITY_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

// fwd
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

// enum
#define MMC_ENUM_BEGIN(name) struct name { enum type {
#define MMC_ENUM_END()       };};

// property
#define MMC_PROPERTY_DEF(type, name) \
	private: \
		type name##_; \
	public: \
		const type& get_##name() const { return name##_; } \
		void set_##name(const type& value) { name##_ = value; } \
/**/

#endif /* MMC_UTILITY_HPP_INCLUDED */
