#pragma once
#include "Figure.h"
class EllipseF :public Figure {
	DECLARE_SERIAL(EllipseF)   //!!! NO ";"  
public:
	// must 4 serialization
	EllipseF() {}
	EllipseF(CPoint p1, CPoint p2);
	EllipseF(CPoint p1, CPoint p2, int ID);
	void Draw(CDC* dc) const;
	bool isInside(const CPoint& P) const;
};
