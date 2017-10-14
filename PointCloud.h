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
#include <string>

class PointCloud : public sf::Transformable{
public:
	PointCloud(const double radius = 1, const sf::Color &col = sf::Color(100,100,100));
	virtual ~PointCloud();

	PointCloud(const PointCloud &obj);

	void addPoint(const double x = 0, const double y = 0, const double r = 10, const int R = 100, const int G = 100, const int B = 100);
//	void generateCloud(const double xLeft, const double xRight, const double yLeft, const double yRight);

	void translate(const double x = 0, const double y = 0);

	void readFromFile(const std::string &path);
	void writeToFile(const std::string path) const;

	void setColor(sf::Color col);

	unsigned int size();

	std::vector<Point> points;
	double radius;	// each point in the pointCloud has this radius

	sf::Color m_color;
};

#endif /* POINTCLOUD_H_ */
