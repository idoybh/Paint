#pragma once
#include "RectangleF.h"

class LineF : public RectangleF {
	DECLARE_SERIAL(LineF)   //!!! NO ";"  
public:
	// must 4 serialization
	LineF() {}

	/**
	Constructs a line from 2 points
	@param p1 starting point
	@param p2 ending point
	*/
	LineF(CPoint p1, CPoint p2);

	/**
	Constructs a line from 2 points
	@param p1 starting point
	@param p2 ending point, assigns specific ID
	@param ID the ID
	*/
	LineF(CPoint p1, CPoint p2, int ID);

	/**
	Checks if a point is proximal to the line
	@param P the point to check
	@return true if proximal, false otherwise
	*/
	bool  isInside(const CPoint& P) const;

	void Draw(CDC* dc) const;
};

