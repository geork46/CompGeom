/* 
 * File:   MainViewer.cpp
 * Author: master
 * 
 * Created on 14 Сентябрь 2012 г., 17:23
 */

#include <QApplication>
#include <QWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include <iostream>

#include "MainViewer.h"

MainViewer::MainViewer()
{
	colors[CLR_CU] = QColor(0, 38, 255);
	colors[CLR_CD] = QColor(0, 198, 200);
	colors[CLR_CDA] = QColor(0, 127, 14);
	colors[CLR_CUA] = QColor(76, 255, 0);
}

bool MainViewer::on_move(point_type const & p)
{
	if (polygons.size() == 0)
		return false;
	selected = algo.contains(p);	
	return true;
}

void MainViewer::draw(drawer_type & drawer)     const
{
	drawer.set_color(Qt::blue);
	for (point_type const & pt : next_cnt)
	    drawer.draw_point(pt, 3);

	for (auto iP = polygons.begin(); iP != polygons.end(); iP++)
	{
		if (iP != selected)
		{
			drawer.set_color(colors[CLR_CU]);
			visualization::draw(drawer, iP->front());
			for (auto cnt = ++iP->begin(); cnt != iP->end(); cnt++)
			{
				drawer.set_color(colors[CLR_CD]);
				visualization::draw(drawer, *cnt);
			}
		} else
		{
			for (auto cnt = iP->begin(); cnt != iP->end(); cnt++)
			{
				drawer.set_color(colors[CLR_CDA]);
				visualization::draw(drawer, *cnt);
			}
		}
	}
}

void MainViewer::print(printer_type & printer)  const
{
	printer.corner_stream() << "Polygon num: " << polygons.size() << endl; 
	if (message != "")
		printer.corner_stream() << ">>" << message;
}

bool MainViewer::on_double_click(point_type const & pt)
{
	message = "";
	// TODO Проверить, не пересекает ли очередное ребро что-нибуль
	next_cnt.push_back(pt);
    return true;
}

bool MainViewer::on_key(int key)
{
	switch (key)
	{
		case Qt::Key_Escape:
			message = "";
			next_cnt.clear();
			return true;
		case Qt::Key_Return: 
			if (next_cnt.size() < 3)
				return false;
			// TODO Проверить, что последнее ребро контура не пересекает других ребер
			contour_type temp_cnt(next_cnt);
			if (polygons.empty())
			{
				if (!GeomAlgo::getDirection(temp_cnt))
				{
					next_cnt.reverse();
					temp_cnt = contour_type(next_cnt);	
				}
				polygons.push_back(polygon_type());
				polygons.back().push_back(temp_cnt);
				algo.init(polygons);
			} else 
			{
				auto it = algo.contains(next_cnt.front());
				if (it == polygons.end())
				{
					if (!GeomAlgo::getDirection(temp_cnt))
					{
						next_cnt.reverse();
						temp_cnt = contour_type(next_cnt);	
					}
					polygons.push_back(polygon_type());
					polygons.back().push_back(temp_cnt);
					algo.init(polygons);
				} else
				{
					if (GeomAlgo::getDirection(temp_cnt))
					{
						next_cnt.reverse();
						temp_cnt = contour_type(next_cnt);	
					}
					it->push_back(temp_cnt);
					algo.init(polygons);
				}
			}
			next_cnt.clear();	
			return true;
//	    case Qt::Key_S:
//	        {
//	            std::string filename = QFileDialog::getSaveFileName(
//	                get_wnd(), 
//	                "Save Points"
//	            ).toStdString();
//	            if (filename != "")
//	            {
//	                std::ofstream out(filename.c_str());
//	                boost::copy(pts_, std::ostream_iterator<point_type>(out, "\n"));
//	            }
//	        }
//	        break;
//	    case Qt::Key_L:
//	        {
//	            std::string filename = QFileDialog::getOpenFileName(
//	                get_wnd(), 
//	                "Load Points"
//	            ).toStdString();
//	            if (filename != "")
//	            {
//	                std::ifstream in(filename.c_str());
//	                std::istream_iterator<point_type> beg(in), end;
//	                pts_.assign(beg, end);
//	                cnt_.reset();
//	                return true;
//	            }
//	        }
    }
    return false;
}
