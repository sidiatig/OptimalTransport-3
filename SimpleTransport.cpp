/*
 * SimpleTransport.cpp
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#include "SimpleTransport.h"
#include <math.h>

#include <iostream>

#include <algorithm>    // for next_permutation

using namespace std;

SimpleTransport::SimpleTransport(){

}

SimpleTransport::SimpleTransport(PointCloud &a, PointCloud &b) {
	// TODO Auto-generated constructor stub
	A = &a;
	B = &b;

	m_matrix.rows = A->size();
	m_matrix.columns = B->size();
	m_matrix.init();
}

SimpleTransport::~SimpleTransport() {
	// TODO Auto-generated destructor stub


}

double SimpleTransport::euclideanDistance(const Point &a, const Point &b){

	double dx = b.getPosition().x-a.getPosition().x;
	double dy = b.getPosition().y-a.getPosition().y;

	double d = dx*dx + dy*dy;
	return sqrt(d);
}

void SimpleTransport::bruteForce(){
	/*
	 * Take the minimum by looking at all permutations.
	 */

	double best_val = 1000000000;
	Matrix best_matrix = m_matrix;

	// need to sort first in order to iterate over all permutations
	sort(m_matrix.m_values.begin(),m_matrix.m_values.end());
	do {

		Matrix cur = m_matrix;
		double cur_val = evaluatePairings(cur);

		if(cur_val <= best_val){
			best_val = cur_val;
			best_matrix = cur;
		}
	} while(m_matrix.nextPermutation());

//	cout << "best distance: " << best_val << endl;

	m_matrix = best_matrix;
}

double SimpleTransport::evaluatePairings(Matrix &m){

	double d = 0;
	for(unsigned int i = 0; i < m.rows; i++){
		m.m_values[i].resize(m.columns);
		for(unsigned int j = 0; j < m.columns; j++){
			if(m.m_values[i][j] == 1){
				d += euclideanDistance(A->points[i], B->points[j])
						*euclideanDistance(A->points[i], B->points[j]);
			}

		}
	}

	return d;
}
