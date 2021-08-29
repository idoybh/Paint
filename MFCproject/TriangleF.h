#pragma once
#include "RectangleF.h"

class TriangleF : public RectangleF
{
	DECLARE_SERIAL(TriangleF)   //!!! NO ";"
public:
	//!! 22 b
	// must 4 serialization
	TriangleF() {}
	//!! 22 b
	TriangleF(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
	bool isInside(const CPoint& P) const;
};

