/* 
 * File:   MainViewer.h
 * Author: master
 *
 * Created on 14 Сентябрь 2012 г., 17:23
 */

#ifndef MAINVIEWER_H
#define	MAINVIEWER_H

#include <algorithm>
#include <vector>
#include <iterator>
#include <memory>
#include <iostream>
#include <visualization/viewer_adapter.h>
#include <visualization/draw_util.h>
#include <io/point.h>
#include <io/contour.h>
#include <QColor>
#include "GeomAlgo.h"

using namespace visualization;
using geom::structures::point_type;
using geom::structures::contour_type;

struct MainViewer : viewer_adapter
{
	MainViewer();
	
	void draw(drawer_type & drawer)     const;
	void print(printer_type & printer)  const;
	
	bool on_double_click(point_type const & pt);
	bool on_key(int key);

	bool on_move(point_type const &);
	
private:
	enum ColorNum {CLR_CU = 0, CLR_CD, CLR_CUA, CLR_CDA};
	QColor colors[4];

	void doCommand();
	std::string						message;
	std::list<polygon_type>::iterator	selected;
	std::list<point_type> 			next_cnt;
	std::list<polygon_type> 		polygons;
	GeomAlgo						algo;
};

#endif	/* MAINVIEWER_H */

