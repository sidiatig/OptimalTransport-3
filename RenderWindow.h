/*
 * RenderWindow.h
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

#include <vector>
#include "PointCloud.h"

#include "SimpleTransport.h"

#include <SFML/Graphics.hpp>

/*
 * Class responsible for drawing the point clouds using SFML.
 */

class RenderWindow {
public:
	RenderWindow();
	virtual ~RenderWindow();

	void addPointCloud(PointCloud * const p);

	void run();

	void addSimpleTransport(SimpleTransport &s);

	unsigned int width;
	unsigned int height;

	std::vector<PointCloud*> pointClouds;

	std::vector<sf::Shape*> m_connections;

	SimpleTransport m_simpleTransport;
};

#endif /* RENDERWINDOW_H_ */
