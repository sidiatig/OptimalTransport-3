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

/*
 * Class responsible for drawing the point clouds using SFML.
 */

class RenderWindow {
public:
	RenderWindow();
	virtual ~RenderWindow();

	void run();

	void addPointCloud(PointCloud * const p);

	unsigned int width;
	unsigned int height;

	std::vector<PointCloud*> pointClouds;
};

#endif /* RENDERWINDOW_H_ */
