#ifndef _CONTOUR_FAKE_H_
#define _CONTOUR_FAKE_H_

#include <vector>

#include "geom/primitives/point.h"
#include "common/range.h"

namespace geom {
namespace structures {

	struct contour_type
	{
		contour_type(contour_type const &)              = delete;
		contour_type& operator = (contour_type const &) = delete;

		contour_type(contour_type && cnt)
		{
			pts_.insert(pts_.begin(), cnt.pts_.begin(), cnt.pts_.end());
		}
		contour_type& operator = (contour_type && cnt)
		{
			pts_.clear();
			pts_.insert(pts_.begin(), cnt.pts_.begin(), cnt.pts_.end());
			return *this;
		}

		typedef std::vector<point_type>::const_iterator const_iterator;

		const_iterator begin()    const { return pts_.begin(); }
		const_iterator end()      const { return pts_.end();   }
		size_t vertices_num() const { return pts_.size(); }
	
		point_type const & operator [] (size_t idx) const { return pts_[idx]; }

		private:
		friend struct contour_builder_type;

		contour_type(std::vector<point_type> && pts);

		std::vector<point_type> pts_;
	};

	typedef common::range_circulator<contour_type> contour_circulator;

}}

#endif /* _CONTOUR_FAKE_H_ */
