#pragma once
//!! 15 b
#include "Figure.h"
class EllipseF :public Figure {
	//!! 21 b
	DECLARE_SERIAL(EllipseF)   //!!! NO ";"  
	//!! 21 e
public:
	//!! 22 b
	// must 4 serialization
	EllipseF() {}
	//!! 22 b
	EllipseF(CPoint p1, CPoint p2);
	void Draw(CDC* dc) const;
};
//!! 15 e
