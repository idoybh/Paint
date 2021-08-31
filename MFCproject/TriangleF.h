#pragma once
#include "RectangleF.h"

class TriangleF : public RectangleF
{
	DECLARE_SERIAL(TriangleF)   //!!! NO ";"
public:
	// must 4 serialization
	TriangleF() {}
	TriangleF(CPoint p1, CPoint p2);
	TriangleF(CPoint p1, CPoint p2, int ID);
	void Draw(CDC* dc) const;
	bool isInside(const CPoint& P) const;
};

