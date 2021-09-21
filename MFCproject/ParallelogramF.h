#pragma once
#include "RectangleF.h"

class ParallelogramF : public RectangleF {
	DECLARE_SERIAL(ParallelogramF)   //!!! NO ";"  

public:
	// must 4 serialization
	ParallelogramF() {}

	/**
	Constructs a parallelogram from 2 points
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	*/
	ParallelogramF(CPoint p1, CPoint p2);

	/**
	Constructs a parallelogram from 2 points, assigns specific ID
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	@param ID the designated ID
	*/
	ParallelogramF(CPoint p1, CPoint p2, int ID);

	void Draw(CDC* dc) const;

	/**
	Checks if a point is inside the parallelogram
	@param P the point to check
	@return true if inside, false otherwise
	*/
	bool isInside(const CPoint& P) const;
};

