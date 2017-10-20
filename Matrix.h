/*
 * Matrix.h
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>

class Matrix {
public:
	Matrix();
	virtual ~Matrix();


	Matrix(unsigned int row, unsigned int col);

	std::vector<std::vector<double>> m_values;

	void init();
	void identity();

	bool nextPermutation();

	void readFromFile(const std::string &path);

	friend std::ostream& operator<< (std::ostream& stream, Matrix& m);

//	friend Matrix& operator*(Matrix &m, Matrix& m);

	unsigned int rows;
	unsigned int columns;
};

#endif /* MATRIX_H_ */
