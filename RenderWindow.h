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
#include "GlobalTransport.h"

#include <SFML/Graphics.hpp>

/*
 * Class responsible for drawing the point clouds using SFML.
 */

enum TRANSPORT{
	SIMPLE,
	GLOBAL
};

class RenderWindow {
public:
	RenderWindow();
	virtual ~RenderWindow();

	void addPointCloud(PointCloud * const p);

	void run();

	void addSimpleTransport(SimpleTransport &s);
	void addGlobalTransport(GlobalTransport &s);

	unsigned int width;
	unsigned int height;

	std::vector<PointCloud*> pointClouds;

	std::vector<sf::Shape*> m_connections;

	TRANSPORT trans;

	SimpleTransport m_simpleTransport;

	GlobalTransport m_globalTransport;
};

#endif /* RENDERWINDOW_H_ */
