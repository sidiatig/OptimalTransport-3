/*
 * PointCloud.cpp
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#include "PointCloud.h"

PointCloud::PointCloud(const double radius, const sf::Color &col) {
	// TODO Auto-generated constructor stub
	this->radius = radius;

	m_color = col;
}

PointCloud::~PointCloud() {
	// TODO Auto-generated destructor stub
}

void PointCloud::addPoint(const double x, const double y){
	Point p(x,y,radius);
	points.push_back(p);
}

void PointCloud::translate(const double x, const double y){
	for(unsigned int i = 0; i < points.size(); i++){
		points[i].move(x,y);
	}
}

PointCloud::PointCloud(const PointCloud &obj) {
   radius = obj.radius;
   points = obj.points;

   m_color = obj.m_color;
}

void PointCloud::setColor(sf::Color col){
	m_color = col;
	for(unsigned int i = 0; i < points.size(); i++){
		points[i].setFillColor(m_color);
	}
}
