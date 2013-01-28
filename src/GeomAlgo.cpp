#include "GeomAlgo.h"

#include <algorithm>
#include <geom/primitives/vector.h>
#include <io/point.h>
#include <iostream>

using geom::structures::vector_type;

double NodeComparator::front;

void GeomAlgo::print() const
{
	for (auto point:points)
	{
		std::cout << *(point.first) <<" ";
	}
	std::cout << "\n";
	for (layer_type const & l : layers)
	{
		std::cout << l.first << ": ";
		for (auto node = l.second.begin(); node != l.second.end(); ++node)
		{
			std::cout << *node->first.e << " ";
		}
		std::cout << "\n";
	}
}

double getXfromEdge(Edge e, double y)
{
	point_type p1 = *e;
	point_type p2 = *(++e);
	double a = 1.0 * (p2.x - p1.x) / (p2.y - p1.y); 
	double b = 1.0 * p1.x - a * p1.y;
	return a * y + b;
}

bool comparePointEdge(point_type const & p, Edge const & e) 
{
	double xe = getXfromEdge(e, p.y);
	return p.x < xe;
}

bool NodeComparator::operator()(Node const &a, Node const &b) const
{
	if (a.type == Node::POINT && b.type == Node::POINT)
		throw std::logic_error("WTF? What are you doing?");
	if (a.type == Node::POINT || b.type == Node::POINT)
	{
		try
		{
			if (a.type == Node::POINT)
			{
				return comparePointEdge(a.p, b.e);
			} else
			{			
				return !comparePointEdge(b.p, a.e);
			}
		} catch(std::logic_error const & e)
		{
			return false;
		}
	} else
	{
		double xa = getXfromEdge(a.e, front);
		double xb = getXfromEdge(b.e, front);
		return xa < xb;
	}
	return true;
}

void GeomAlgo::init(std::list<polygon_type> & polygons)
{
	points.clear();
	layers.clear();
	end_iterator = polygons.end();
	for	(polygon_iterator p = polygons.begin(); p != polygons.end(); ++p)
	{
		for (auto cnt = p->begin(); cnt != p->end(); ++cnt)
		{
	        contour_circulator beg(*cnt), it = beg;
	        do
	        {
				points.push_back(point_pair(it, p));
	            ++it;
	        } while (it != beg);
		}
	}
	std::sort(points.begin(), points.end(), 
		[](point_pair a, point_pair b)
		{
			return (a.first->y < b.first->y); 
		});	
	layer_type t;
	t.second.clear();
	double oldY = (points.size() > 0) ? 0.5 + points[0].first->y : 0;
	for (int i = 0; i < points.size(); ++i)
	{
		NodeComparator::front = oldY;

		contour_circulator p = points[i].first;
		if ((++p)->y < points[i].first->y)
			t.second.erase(Node(points[i].first));
		p = points[i].first;
		if ((--p)->y < points[i].first->y)
			t.second.erase(Node(p));

		NodeComparator::front = 0.5 + points[i].first->y;

		p = points[i].first;
		if ((++p)->y > points[i].first->y)
			t.second[Node(points[i].first)] = points[i].second;
		p = points[i].first;
		if ((--p)->y > points[i].first->y)
			t.second[Node(p)] = points[i].second;
		if (i + 1 == points.size() || points[i + 1].first->y != points[i].first->y)
		{
			t.first = points[i].first->y;
			layers.push_back(t);
			oldY = NodeComparator::front;
		}
	}
}

polygon_iterator GeomAlgo::contains(point_type const & p) const
{
	if (layers.size() == 0 || p.y < layers[0].first)
		return end_iterator;
	size_t l = 0, r = layers.size() - 1;
	while (l < r)
	{
		size_t m = (l + r) / 2 + 1;
		if (p.y >= layers[m].first)
			l = m;	
		else
			r = m - 1;
	}
	layer_type const & layer = layers[l];
	auto it = layer.second.lower_bound(Node(p));
	if (it == layer.second.end() || it == layer.second.begin() || (--it) == layer.second.end())
		return end_iterator;
	contour_circulator outside(it->first.e);
	point_type p1 = *(outside), p2 = *(++outside);
	vector_type	v1(-100, 0), v2(p2.x - p1.x, p2.y - p1.y);
	if ((v1 ^ v2) > 0)
		return it->second;
	else
		return end_iterator;
}

bool GeomAlgo::getDirection(contour_type const & cnt)
{
	int32 xMax = - (1 << 31);	
	contour_circulator beg(cnt), it = beg, outside(cnt);
	
	do
	{
	    point_type pt = *it;
		if (pt.x > xMax)
		{
			xMax = pt.x;
			outside = it;
		}
	    ++it;
	} while (it != beg);

	point_type p1 = *(--outside), p2 = *(++outside), p3 = *(++outside);
	
	vector_type	v1(p2.x - p1.x, p2.y - p1.y), v2(p3.x - p2.x, p3.y - p2.y);

	return (v1 ^ v2) > 0;
}
