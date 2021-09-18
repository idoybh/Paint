#pragma once
#include "Figure.h"
class EllipseF :public Figure {
	DECLARE_SERIAL(EllipseF)   //!!! NO ";"  
public:
	// must 4 serialization
	EllipseF() {}

	/**
	Constructs an EllipseF from 2 points
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	*/
	EllipseF(CPoint p1, CPoint p2);

	/**
	Constructs an EllipseF from 2 points, assigns specific ID
	@param p1 top left corner of the bounding rectangle
	@param p2 bottom right corner of the bounding rectangle
	@param ID the designated ID
	*/
	EllipseF(CPoint p1, CPoint p2, int ID);

	void Draw(CDC* dc) const;

	/**
	Checks if a point is inside the EllipseF
	@param P the point to check
	@return true if inside, false otherwise
	*/
	bool isInside(const CPoint& P) const;
};
