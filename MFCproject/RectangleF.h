#pragma once
#include "Figure.h"
class RectangleF : public Figure {
	DECLARE_SERIAL(RectangleF)   //!!! NO ";"  

public:
	// must 4 serialization
	RectangleF() {}
	RectangleF(CPoint p1, CPoint p2);
	virtual void Draw(CDC* dc) const {
		Figure::Draw(dc);
	}
};
