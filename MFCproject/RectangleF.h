#pragma once
//!! 14 b
#include "Figure.h"
class RectangleF : public Figure {
	//!! 21 b
	DECLARE_SERIAL(RectangleF)   //!!! NO ";"  
	//!! 21 e
public:
	//!! 22 b
	// must 4 serialization
	RectangleF() {}
	//!! 22 b
	RectangleF(CPoint p1, CPoint p2);
};
//!! 14 e
