/*
 * Point.h
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#ifndef POINT_H_
#define POINT_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
 * Representing one point in 2 dimensional space in the pointcloud.
 * The radius also represents the weight
 */

class Point : public sf::CircleShape{
public:

//	double x;
//	double y;

	Point(const double x = 0, const double y = 0, const double radius = 10, const int R = 100, const int G = 100, const int B = 100);
	virtual ~Point();

	Point(const Point &p);

	friend std::ostream& operator<< (std::ostream& stream, const Point& p);
};

#endif /* POINT_H_ */
