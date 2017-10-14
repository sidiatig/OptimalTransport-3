/*
 * Correspondence.h
 *
 *  Created on: 13.10.2017
 *      Author: willy
 */

#ifndef CORRESPONDENCE_H_
#define CORRESPONDENCE_H_

#include "Point.h"
#include "PointCloud.h"
#include <vector>

class Correspondence {
public:
	Correspondence(PointCloud &A, PointCloud &B);
	virtual ~Correspondence();

	void initMatrix();

	std::vector<std::vector<double>> m_matrix;

	PointCloud *A;
	PointCloud *B;
};

#endif /* CORRESPONDENCE_H_ */
