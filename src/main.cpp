/*
 * File:   main.cpp
 * Author: master
 *
 * Created on 14 Сентябрь 2012 г., 17:20
 */

#include <QApplication>

#include "MainViewer.h"



int main(int argc, char **argv)
{
	QApplication app(argc, argv);	
	MainViewer viewer;
	visualization::run_viewer(&viewer, "Localization in polygons");

}

