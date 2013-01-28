#ifndef _EXTRA_H_
#define _EXTRA_H_

#include <geom/primitives/vector.h>

namespace geom {
namespace structures {
namespace extra {

	struct IPoint : point_type 
	{
		point_type *prev, *next;
	};
	
	struct Edge
	{
		IPoint *u, *v;
	}

}}}

#endif /* _EXTRA_H_ */
