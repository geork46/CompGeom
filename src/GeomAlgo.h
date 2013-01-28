#ifndef GEOMALGO_H
#define GEOMALGO_H

#include <list>
#include <vector>
#include <map>
#include <stdexcept>
#include <utility>
#include <geom/primitives/contour.h>
#include <type_aliases.h>

using geom::structures::contour_type;
using geom::structures::point_type;
using geom::structures::contour_circulator;

typedef std::list<contour_type> polygon_type;
typedef std::list<polygon_type>::iterator polygon_iterator;
typedef std::pair<contour_circulator, polygon_iterator> point_pair;
typedef contour_circulator Edge;

struct Node
{
	enum TypeNode {EDGE, POINT};
	TypeNode type;
	Edge const *e;
	point_type const *p;	
	Node(Edge const &e) : e(new Edge(e)), p(0), type(EDGE){}
	Node(point_type const p) : e(0), p(new point_type(p)), type(POINT){}
	// TODO Устранить утечки памяти здесь
};

struct NodeComparator
{
	static double front;
	bool operator()(Node const &, Node const &) const;
};

typedef std::pair<int32, std::map<Node, polygon_iterator, NodeComparator>> layer_type;

class GeomAlgo
{
public:
	static bool getDirection(contour_type const &);
	void init(std::list<polygon_type> &);	
	polygon_iterator contains(point_type const &) const;
	void print() const;
	
private:
	std::vector<point_pair> points;
	std::vector<layer_type> layers;
	polygon_iterator		end_iterator;
};

#endif /* GEOMALGO_H */
