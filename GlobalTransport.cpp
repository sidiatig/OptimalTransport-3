/*
 * GlobalTransport.cpp
 *
 *  Created on: 15.10.2017
 *      Author: willy
 */

#include "GlobalTransport.h"

#include <iostream>

using namespace std;

GlobalTransport::GlobalTransport(){

}

GlobalTransport::GlobalTransport(PointCloud &a, PointCloud &b) {
	// TODO Auto-generated constructor stub
	A = &a;
	B = &b;

	m_matrix.rows = A->size();
	m_matrix.columns = B->size();
	m_matrix.init();

	A->createDistanceMatrix();
	B->createDistanceMatrix();

}

GlobalTransport::~GlobalTransport() {
	// TODO Auto-generated destructor stub
}

void GlobalTransport::bruteForce(){
	/*
	 * Take the minimum by looking at all permutations.
	 */

	double best_val = 100000000000;
	Matrix best_matrix = m_matrix;

	// need to sort first in order to iterate over all permutations
	sort(m_matrix.m_values.begin(),m_matrix.m_values.end());
	sort(B->m_distances.m_values.begin(),B->m_distances.m_values.end());

	int count = 0;
	do {

		Matrix cur = m_matrix;
		double cur_val = evaluatePairings(A->m_distances, B->m_distances);

		if(cur_val <= best_val){
			best_val = cur_val;
			best_matrix = cur;
		}

		count++;
		cout << count << ": " << cur_val << endl;
	} while(m_matrix.nextPermutation() && B->m_distances.nextPermutation());

	cout << "best distance: " << best_val << endl;

	m_matrix = best_matrix;
}

// the distance-matrices of mA and mB need to be permutated at this point
double GlobalTransport::evaluatePairings(Matrix &mA, Matrix &mB){

	double d = 0;
	for(unsigned int i = 0; i < mA.rows; i++){
		for(unsigned int j = 0; j < mA.columns; j++){
				d += (mA.m_values[i][j] - mB.m_values[i][j])
						*(mA.m_values[i][j] - mB.m_values[i][j]);
		}
	}

	return d;
}
