//============================================================================
// Name        : OptimalTransport.cpp
// Author      : Willy Bruhn
// Version     :
// Copyright   : 
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "RenderWindow.h"
#include "PointCloud.h"
#include "Point.h"

#include "SimpleTransport.h"
#include "GlobalTransport.h"

#include <iostream>

using namespace std;

int main(void) {

	PointCloud pCloud(10,sf::Color(100,100,100));
	pCloud.readFromFile("./PointClouds/pc1.txt");

	PointCloud pCloud2(10,sf::Color(100,100,250));
	pCloud2.readFromFile("./PointClouds/pc2.txt");

	SimpleTransport trans(pCloud,pCloud2);
//	trans.bruteForce();

	GlobalTransport trans2(pCloud,pCloud2);
	trans2.bruteForce();

	RenderWindow win;
	win.addPointCloud(&pCloud);
	win.addPointCloud(&pCloud2);
	//win.addSimpleTransport(trans);

	win.trans = TRANSPORT::GLOBAL;
	win.addGlobalTransport(trans2);

//	win.trans = TRANSPORT::SIMPLE;
//	win.addSimpleTransport(trans);

	win.run();


	pCloud.writeToFile("./PointClouds/pc1.txt");
	pCloud2.writeToFile("./PointClouds/pc2.txt");

	return EXIT_SUCCESS;
}
