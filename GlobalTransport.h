/*
 * GlobalTransport.h
 *
 *  Created on: 15.10.2017
 *      Author: willy
 */

#ifndef GLOBALTRANSPORT_H_
#define GLOBALTRANSPORT_H_

#include "Point.h"
#include "PointCloud.h"

#include <vector>
#include "Matrix.h"

class GlobalTransport {
public:
	GlobalTransport();
	GlobalTransport(PointCloud &a, PointCloud &b);
	virtual ~GlobalTransport();


	double evaluatePairings(Matrix &mA, Matrix &mB);

	void bruteForce();


	PointCloud *A;
	PointCloud *B;

	Matrix m_matrix;

};

#endif /* GLOBALTRANSPORT_H_ */
