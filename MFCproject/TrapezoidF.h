#pragma once
#include "RectangleF.h"

class TrapezoidF : public RectangleF {
	DECLARE_SERIAL(TrapezoidF)   //!!! NO ";"  

public:
	// must 4 serialization
	TrapezoidF() {}

	/**
	Constructs a trapezoid from 2 points
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	*/
	TrapezoidF(CPoint p1, CPoint p2);

	/**
	Constructs a trapezoid from 2 points, assigns specific ID
	@param p1 top left corner
	@param p2 bottom right corner
	@param ID the designated ID
	*/
	TrapezoidF(CPoint p1, CPoint p2, int ID);

	void Draw(CDC* dc) const;

	/**
	Checks if a point is inside the trapezoid
	@param P the point to check
	@return true if inside, false otherwise
	*/
	bool isInside(const CPoint& P) const;
};

