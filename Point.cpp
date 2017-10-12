/*
 * Point.cpp
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#include "Point.h"

Point::Point(const double x, const double y, const double radius) :sf::CircleShape() {
	// TODO Auto-generated constructor stub
//	this->x = x;
//	this->y = y;

//	m_shape = new sf::CircleShape();
	setPosition(x,y);
	setFillColor(sf::Color(100, 250, 50));
	setRadius(radius);

	setOrigin(0,0);
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Point::Point(const Point &p){
	setPosition(p.getPosition());
	setFillColor(p.getFillColor());
	setRadius(p.getRadius());

	setOrigin(p.getOrigin());
}
