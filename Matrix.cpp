/*
 * Matrix.cpp
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#include "Matrix.h"
#include <algorithm>    // for next_permutation

Matrix::Matrix(){
	rows = 0;
	columns = 0;
};

Matrix::Matrix(unsigned int row, unsigned int col) {
	rows = row;
	columns = col;

	init();
}

Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
}

bool Matrix::nextPermutation(){
	return next_permutation(m_values.begin(), m_values.end());
}

void Matrix::init(){
	m_values.resize(rows);
	for(unsigned int i = 0; i < rows; i++){
		m_values[i].resize(columns);
		for(unsigned int j = 0; j < columns; j++){
			if(i == j)
				m_values[i][j] = 1;
			else
				m_values[i][j] = 0;
		}
	}
}
