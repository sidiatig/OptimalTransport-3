/*
 * PointCloud.cpp
 *
 *  Created on: 11.10.2017
 *      Author: willy
 */

#include "PointCloud.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

PointCloud::PointCloud(const double radius, const sf::Color &col) {
	// TODO Auto-generated constructor stub
	this->radius = radius;

	m_color = col;

	m_distances.columns = points.size();
	m_distances.rows = points.size();
	m_distances.init();

}

PointCloud::~PointCloud() {
	// TODO Auto-generated destructor stub
}

void PointCloud::addPoint(const double x, const double y, const double r,
							const int R, const int G, const int B){
	Point p(x,y,r, R, G, B);
	points.push_back(p);
}

void PointCloud::translate(const double x, const double y){
	for(unsigned int i = 0; i < points.size(); i++){
		points[i].move(x,y);
	}
}

PointCloud::PointCloud(const PointCloud &obj) {
   radius = obj.radius;
   points = obj.points;

   m_color = obj.m_color;
}

void PointCloud::setColor(sf::Color col){
	m_color = col;
	for(unsigned int i = 0; i < points.size(); i++){
		points[i].setFillColor(m_color);
	}
}

unsigned int PointCloud::size(){
	return points.size();
}

void PointCloud::readFromFile(const std::string &path){

	points.clear();

	cerr << "readSettings from " << path << endl;

		string line;
		ifstream myfile (path);
		if (myfile.is_open())
		{
			while ( getline (myfile,line) )
			{
				vector<string> result;
				stringstream ss;
				ss << line;
				while( ss.good() )
				{
				    string substr;
				    getline( ss, substr, ';' );
				    result.push_back( substr );
				}

				if(result[0].c_str()[0] != '#'){
					addPoint(std::atoi(result[0].c_str()), std::atoi(result[1].c_str()), std::atoi(result[2].c_str()),
							std::atoi(result[3].c_str()), std::atoi(result[4].c_str()), std::atoi(result[5].c_str()));
				}

			}
			myfile.close();
		}

		else cout << "Unable to open file " << path << endl;
}

void PointCloud::writeToFile(const std::string path) const{
	cerr << "Writing Settings to file " << path << endl;

	// /todo check if file-opening was succesful
	ofstream myfile;
	myfile.open (path.c_str());


	myfile << "#x;y;radius;r;g;b\n";
	for(unsigned int i = 0; i < points.size(); i++){
		myfile << points[i];
	}


//	for(unsigned int i = 0; i < playerLeftKeys.size(); i++){
//		string left =  playerLeftKeys[i].getString();
//		string right =  playerRightKeys[i].getString();
//		myfile << "Player;" << i << ";" << left << ";" << right << endl;
//	}

	myfile.close();
}

void PointCloud::createDistanceMatrix(){

	m_distances.columns = points.size();
	m_distances.rows = points.size();
	m_distances.init();

	for(unsigned int i = 0; i < points.size(); i++){
		for(unsigned int j = 0; j < points.size(); j++){
			m_distances.m_values[i][j] = euclideanDistance(points[i],points[j]);
		}
	}
}


