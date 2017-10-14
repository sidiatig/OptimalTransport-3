/*
 * SimpleTransport.h
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#ifndef SIMPLETRANSPORT_H_
#define SIMPLETRANSPORT_H_

#include <map>

#include "Point.h"
#include "PointCloud.h"

#include <vector>
#include "Matrix.h"

class SimpleTransport {
public:
	SimpleTransport();

	SimpleTransport(PointCloud &A, PointCloud &B);
	virtual ~SimpleTransport();

	void bruteForce();

	double euclideanDistance(const Point &a, const Point &b);

	double evaluatePairings(Matrix &m);

	PointCloud *A;
	PointCloud *B;

	Matrix m_matrix;
};

#endif /* SIMPLETRANSPORT_H_ */
