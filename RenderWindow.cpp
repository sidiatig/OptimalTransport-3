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
#include <math.h>

using namespace std;

RenderWindow::RenderWindow() {
	// TODO Auto-generated constructor stub

	width = 800;
	height = 600;

	scalingFactor = 50;
	m_connectionsVisible = true;
}

RenderWindow::~RenderWindow() {
	// TODO Auto-generated destructor stub
}

double distance(const sf::Vector2f &v1, const sf::Vector2f &v2){
	double dx = v1.x-v2.x;
	double dy = v1.y-v2.y;
	return sqrt(dx*dx + dy*dy);
}

void RenderWindow::run()
{
    // Let's setup a window
	sf::RenderWindow window(sf::VideoMode(width, height), "2d Transport");

    sf::Vector2f oldPos;
    bool moving = false;
    bool objMoving = false;
    sf::CircleShape * movingObj;

    PointCloud * movingPointCloud;

    //buttons
    sf::RectangleShape calculateButton(sf::Vector2f(200, 100));


    float zoom = 1;

    // Retrieve the window's default view
    sf::View view = window.getDefaultView();

    sf::View menu(sf::Vector2f(350, 300), sf::Vector2f(300, 200));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    // Mouse button is pressed, get the position and set moving as active
                    if (event.mouseButton.button == 1) {
                        moving = true;
                        oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                    // Mouse button is pressed, get the position and check if it is pressed on a Point
                    else if (event.mouseButton.button == 0) {


                        oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                        for(unsigned int i = 0; i < pointClouds.size(); i++){
                            for(unsigned int j = 0; j < pointClouds[i]->points.size(); j++){
                            	if (distance(oldPos,pointClouds[i]->points[j].getPosition()) <  pointClouds[i]->points[j].getRadius()){
                            		objMoving = true;
                            		movingObj = &pointClouds[i]->points[j];
                            		movingPointCloud = pointClouds[i];
                            	}
                            }
                        }
                    }
                    break;
                case  sf::Event::MouseButtonReleased:
                    // Mouse button is released, no longer move
                    if (event.mouseButton.button == 1) {
                        moving = false;
                    }
                    else if (event.mouseButton.button == 0 && objMoving == true) {
                        objMoving = false;

						movingPointCloud->createDistanceMatrix();

                        if(trans == SIMPLE){
							m_simpleTransport.bruteForce();
							addSimpleTransport(m_simpleTransport);
                        }
                        else if(trans == GLOBAL){

                        	m_globalTransport.bruteForce();
                        	addGlobalTransport(m_globalTransport);
                        }
                        else if(trans == EXTERN){

                        	cerr << "Calling R-script here!" << endl;

                        	string Rcall = "./Rscripts/./LOPgeneralNbyN.R";
                        	system(Rcall.c_str());

                    		readInMatchingMeasure(m_matchingMeasure, "./MatchingMeasures/mymatrix.csv");
                    		createConnectionsWithMatchingMeasure(m_connections,m_matchingMeasure);
                        }
                    }
                    break;

                case sf::Event::MouseMoved:
                    {
                        // Ignore mouse movement unless a button is pressed (see above)
                        if (moving == false && objMoving == false)
                            break;
                        // Determine the new position in world coordinates
                        const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                        // Determine how the cursor has moved
                        // Swap these to invert the movement direction
                        const sf::Vector2f deltaPos = oldPos - newPos;

                        if(moving){
							// Move our view accordingly and update the window
							view.setCenter(view.getCenter() + deltaPos);
							window.setView(view);
                        }
                        else if(objMoving){
                        	movingObj->move(-deltaPos);
                        }

						// Save the new position as the old one
						// We're recalculating this, since we've changed the view
						oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                        break;
                    }
                case sf::Event::MouseWheelMoved:
                    // Ignore the mouse wheel unless we're not moving
                    if (moving)
                        break;

                    // Determine the scroll direction and adjust the zoom level
                    // Again, you can swap these to invert the direction
                    if (event.mouseWheel.delta <= -1)
                        zoom = std::min(10.f, zoom + .1f);
                    else if (event.mouseWheel.delta >= 1)
                        zoom = std::max(.1f, zoom - .1f);

                    // Update our view
                    view.setSize(window.getDefaultView().getSize()); // Reset the size
                    view.zoom(zoom); // Apply the zoom level (this transforms the view)
                    window.setView(view);
                    break;
            }
        }

        // Draw our simple scene
        window.clear(sf::Color::White);
//        window.setView(view);

        for(unsigned int i = 0; i < pointClouds.size(); i++){
            for(unsigned int j = 0; j < pointClouds[i]->points.size(); j++){
            	window.draw((sf::CircleShape) pointClouds[i]->points[j]);
            }
        }

        for(unsigned int i = 0; i < m_connections.size(); i++){
        	window.draw(*m_connections[i]);
        }

//        window.setView(menu);
//        window.draw(calculateButton);

        window.display();

//        m_simpleTransport.bruteForce();
//        addSimpleTransport(m_simpleTransport);
    }
}

void RenderWindow::addPointCloud(PointCloud * const p){
	pointClouds.push_back(p);
}

void RenderWindow::addSimpleTransport(SimpleTransport &s){
	m_simpleTransport = s;

	double thickness = 3;

	m_connections.clear();

    for(unsigned int i = 0; i < m_simpleTransport.A->size(); i++){
        for(unsigned int j = 0; j < m_simpleTransport.B->size(); j++){
        	if(m_simpleTransport.m_matrix.m_values[i][j] == 1){
        		double dx = m_simpleTransport.A->points[i].getPosition().x
							- m_simpleTransport.B->points[j].getPosition().x;

        		double dy = m_simpleTransport.A->points[i].getPosition().y
							- m_simpleTransport.B->points[j].getPosition().y;

        		double dist = sqrt(dx*dx + dy*dy);

				sf::RectangleShape *s = new sf::RectangleShape(sf::Vector2f(dist, thickness));

//				s->setPosition(m_simpleTransport.A->points[i].getPosition());

				s->setPosition(m_simpleTransport.A->points[i].getPosition().x,
								m_simpleTransport.A->points[i].getPosition().y - thickness/2.0);
				s->setFillColor(sf::Color(250,0,0));

				if(dy > 0){

					double alpha = -acos((dx)/ -dist) * (180 / M_PI);
//					s->setOrigin(dist/2.0, thickness/2.0);
					s->rotate(alpha);
				} else{
					double alpha = acos((dx)/ -dist) * (180 / M_PI);
//					s->setOrigin(dist/2.0, thickness/2.0);
					s->rotate(alpha);
				}

				m_connections.push_back(s);
        	}
        }
    }
}

void RenderWindow::addGlobalTransport(GlobalTransport &s){
	m_globalTransport = s;

	double thickness = 3;

	m_connections.clear();

    for(unsigned int i = 0; i < m_globalTransport.A->size(); i++){
        for(unsigned int j = 0; j < m_globalTransport.B->size(); j++){
        	if(m_globalTransport.m_matrix.m_values[i][j] == 1){
        		double dx = m_globalTransport.A->points[i].getPosition().x
							- m_globalTransport.B->points[j].getPosition().x;

        		double dy = m_globalTransport.A->points[i].getPosition().y
							- m_globalTransport.B->points[j].getPosition().y;

        		double dist = sqrt(dx*dx + dy*dy);

				sf::RectangleShape *s = new sf::RectangleShape(sf::Vector2f(dist, thickness));

//				s->setPosition(m_simpleTransport.A->points[i].getPosition());

				s->setPosition(m_globalTransport.A->points[i].getPosition().x,
						m_globalTransport.A->points[i].getPosition().y - thickness/2.0);
				s->setFillColor(sf::Color(250,0,0));

				if(dy > 0){

					double alpha = -acos((dx)/ -dist) * (180 / M_PI);
//					s->setOrigin(dist/2.0, thickness/2.0);
					s->rotate(alpha);
				} else{
					double alpha = acos((dx)/ -dist) * (180 / M_PI);
//					s->setOrigin(dist/2.0, thickness/2.0);
					s->rotate(alpha);
				}

				m_connections.push_back(s);
        	}
        }
    }
}


void RenderWindow::readInMatchingMeasure(Matrix &m, const std::string &path){

	bool old = false;
	Matrix cpy = m;
	// check if the matrix changed
	if(m.m_values.size() != 0 && m.m_values[0].size() != 0){
		old = true;
	}


	m.readFromFile(path);
	cerr << "Measure:\n" << m << endl;

	double sum = 0.0;
	double diff = 0.0;
	for(unsigned int i = 0; i < m.m_values.size(); i++){
		for(unsigned int j = 0; j < m.m_values[i].size(); j++){
			sum += m.m_values[i][j];
			if(old)
				diff += fabs(cpy.m_values[i][j] - m.m_values[i][j]);
		}
	}

	if(diff == 0)
		cerr << "WARNING: Measure did not change! (bool old = " << old << ")" << endl;


	if(fabs(sum - 1.0) > 0.1)
		cerr << "WARNING: Measure does not sum to 1!\n"
				"sum = " << sum << endl;
}

void RenderWindow::createConnectionsWithMatchingMeasure(std::vector<sf::Shape*> &con, const Matrix &m){

	double thickness = 0;

	m_connections.clear();

	A->calculateTotalMass();
	B->calculateTotalMass();

    for(unsigned int i = 0; i < A->size(); i++){
        for(unsigned int j = 0; j < B->size(); j++){
        	// only draw a line if there is actually some mass transported between the points
        	thickness = m.m_values[i][j] * A->m_totalMass*2;
        	if(thickness > 0){
        		double dx = A->points[i].getPosition().x
							- B->points[j].getPosition().x;

        		double dy = A->points[i].getPosition().y
							- B->points[j].getPosition().y;

        		double dist = sqrt(dx*dx + dy*dy);

				sf::RectangleShape *s = new sf::RectangleShape(sf::Vector2f(dist, thickness));

				s->setFillColor(sf::Color(250,0,0));

				double alpha = 0;
				if(dy > 0){
					alpha = -acos((dx)/ -dist) * (180 / M_PI);
//					s->setOrigin(dist/2.0, thickness/2.0);

				} else{
					alpha = acos((dx)/ -dist) * (180 / M_PI);
//					s->setOrigin(dist/2.0, thickness/2.0);
				}


				s->setPosition(A->points[i].getPosition().x,
								A->points[i].getPosition().y);

				s->setOrigin(0,thickness/2.0);

				s->rotate(alpha);

				m_connections.push_back(s);
        	}
        }
    }
}
