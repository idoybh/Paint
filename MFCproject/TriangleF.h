#pragma once
#include "Figure.h"
class TriangleF : public Figure
{
	DECLARE_SERIAL(TriangleF)   //!!! NO ";"  
public:
	//!! 22 b
	// must 4 serialization
	TriangleF() {}
	//!! 22 b
	TriangleF(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};

