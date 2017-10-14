/*
 * Correspondence.cpp
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#include "Correspondence.h"

Correspondence::Correspondence(PointCloud &a, PointCloud &b) {
	// TODO Auto-generated constructor stub

	A = &a;
	B = &b;

	initMatrix();
}

Correspondence::~Correspondence() {
	// TODO Auto-generated destructor stub
}

void Correspondence::initMatrix(){

	m_matrix.resize(A->size());
	for(unsigned int i = 0; i < A->size(); i++){
		m_matrix[i].resize(B->size());
		for(unsigned int j = 0; j < B->size(); j++){
			m_matrix[i][j] = 0;
		}
	}
}
