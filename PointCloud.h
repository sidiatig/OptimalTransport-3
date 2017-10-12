/*
 * PointCloud.h
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include "Point.h"
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class PointCloud : public sf::Transformable{
public:
	PointCloud(const double radius = 1, const sf::Color &col = sf::Color(100,100,100));
	virtual ~PointCloud();

	PointCloud(const PointCloud &obj);

	void addPoint(const double x = 0, const double y = 0);
//	void generateCloud(const double xLeft, const double xRight, const double yLeft, const double yRight);

	void translate(const double x = 0, const double y = 0);

	void setColor(sf::Color col);

	std::vector<Point> points;
	double radius;	// each point in the pointCloud has this radius

	sf::Color m_color;
};

#endif /* POINTCLOUD_H_ */
