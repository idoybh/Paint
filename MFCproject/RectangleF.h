#pragma once
#include "Figure.h"
class RectangleF : public Figure {
	DECLARE_SERIAL(RectangleF)   //!!! NO ";"  

public:
	// must 4 serialization
	RectangleF() {}

	/**
	Constructs a rectangle from 2 points
	@param p1 top left corner
	@param p2 bottom right corner
	*/
	RectangleF(CPoint p1, CPoint p2);

	/**
	Constructs a rectangle from 2 points, assigns specific ID
	@param p1 top left corner
	@param p2 bottom right corner
	@param ID the designated ID
	*/
	RectangleF(CPoint p1, CPoint p2, int ID);

	virtual void Draw(CDC* dc) const {
		Figure::Draw(dc);
	}
};
