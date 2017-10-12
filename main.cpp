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

#include <iostream>

using namespace std;

int main(void) {

	PointCloud pCloud(10,sf::Color(100,100,100));
	pCloud.addPoint(100,100);
	pCloud.addPoint(100,150);
	pCloud.addPoint(250,500);
	pCloud.addPoint(290,400);
	pCloud.addPoint(400,500);
	pCloud.addPoint(200,500);

	PointCloud pCopy = pCloud;
	pCopy.translate(600,300);
//	pCopy.m_color = sf::Color(250,100,250);
	pCopy.setColor(sf::Color(250,100,250));

	cout << pCloud.points.size() << endl;
	for(int i = 0; i < pCloud.points.size(); i++){
//		cout << "old " << pCloud.points[i]->getPosition().x << " " << pCloud.points[i]->getPosition().y << endl;
//		cout << "new " << pCopy.points[i].getPosition().x << " " << pCopy.points[i].getPosition().y << endl;
	}



	RenderWindow win;
	win.addPointCloud(&pCloud);
	win.addPointCloud(&pCopy);
	win.run();




	return EXIT_SUCCESS;
}
