/*
 * Matrix.h
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

class Matrix {
public:
	Matrix();
	virtual ~Matrix();


	Matrix(unsigned int row, unsigned int col);

	std::vector<std::vector<int>> m_values;

	void init();

	bool nextPermutation();

	unsigned int rows;
	unsigned int columns;
};

#endif /* MATRIX_H_ */
