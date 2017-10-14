/*
 * Point.cpp
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#include "Point.h"
#include <iostream>
#include <string>

Point::Point(const double x, const double y, const double radius, const int R, const int G, const int B) :sf::CircleShape() {
	// TODO Auto-generated constructor stub
//	this->x = x;
//	this->y = y;

//	m_shape = new sf::CircleShape();
	setPosition(x,y);
	setFillColor(sf::Color(R, G, B));
	setRadius(radius);

	setOrigin(radius,radius);
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

std::ostream& operator<< (std::ostream& stream, const Point& p){
	stream << p.getPosition().x << ";" << p.getPosition().y << ";" << p.getRadius() << ";"
			<< std::to_string(p.getFillColor().r) << ";" << std::to_string(p.getFillColor().g) << ";" << std::to_string(p.getFillColor().b) << ";" << std::endl;
	return stream;
}
