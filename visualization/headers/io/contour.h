#ifndef _CONTOUR_IO_H_
#define _CONTOUR_IO_H_

#include "geom/primitives/contour.h"

namespace geom {
namespace structures {

//    std::istream & operator >> (std::istream & in, contour_type & cnt);
    std::ostream & operator << (std::ostream & out, contour_type const & cnt);

}}

#endif /* __CONTOUR_IO_H_ */
