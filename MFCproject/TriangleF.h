#pragma once
#include "RectangleF.h"

class TriangleF : public RectangleF
{
private:

public:
	DECLARE_SERIAL(TriangleF)   //!!! NO ";"
	// must 4 serialization
	TriangleF() {}

	/**
	Constructs a triangle from 2 points
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	*/
	TriangleF(CPoint p1, CPoint p2);

	/**
	Constructs a triangle from 2 points, assigns specific ID
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	@param ID the designated ID
	*/
	TriangleF(CPoint p1, CPoint p2, int ID);

	void Draw(CDC* dc) const;

	/**
	Checks if a point is inside the triangle
	@param P the point to check
	@return true if inside, false otherwise
	*/
	bool isInside(const CPoint& P) const;
};

