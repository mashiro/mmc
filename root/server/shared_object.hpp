#ifndef MMC_SHARED_OBJECT_HPP_INCLUDED
#define MMC_SHARED_OBJECT_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#define MMC_ENABLE_SHARED_THIS(type) \
	boost::shared_ptr<type> shared_this() \
	{ \
		return boost::shared_static_cast<type>(shared_from_this()); \
	} \
	boost::shared_ptr<type const> shared_this() const \
	{ \
		return boost::shared_static_cast<type const>(shared_from_this()); \
	} \
/**/

namespace mmc {

class SharedObject
	: public boost::enable_shared_from_this<SharedObject>
{
public:
	virtual ~SharedObject() {}
};

} // namespace mmc

#endif /* MMC_SHARED_OBJECT_HPP_INCLUDED */
