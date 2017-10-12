/*
 * RenderWindow.cpp
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#include <iostream>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "RenderWindow.h"

#include "Point.h"

using namespace std;

RenderWindow::RenderWindow() {
	// TODO Auto-generated constructor stub

	width = 800;
	height = 600;
}

RenderWindow::~RenderWindow() {
	// TODO Auto-generated destructor stub
}

void RenderWindow::run(){
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

// change the position of the window (relatively to the desktop)
window.setPosition(sf::Vector2i(10, 50));

// change the size of the window
//window.setSize(sf::Vector2u(640, 480));

// change the title of the window
window.setTitle("2d Shape Recognition");

sf::View view(sf::FloatRect(0, 0, width, height));


view.zoom(2);
window.setView(view);


sf::CircleShape circle;
circle.setRadius(150);
circle.setOutlineColor(sf::Color::Red);
circle.setOutlineThickness(5);
circle.setPosition(100, 200);


while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for(unsigned int i = 0; i < pointClouds.size(); i++){
        	cout << pointClouds[i]->points.size() << endl;
            for(unsigned int j = 0; j < pointClouds[i]->points.size(); j++){
            	window.draw((sf::CircleShape) pointClouds[i]->points[j]);
            }
        }



        // end the current frame
        window.display();
    }


}

void RenderWindow::addPointCloud(PointCloud * const p){
	pointClouds.push_back(p);
}

