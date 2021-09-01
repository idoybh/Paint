#pragma once
#include "RectangleF.h"

class LineF : public RectangleF {
	DECLARE_SERIAL(LineF)   //!!! NO ";"  
public:
	// must 4 serialization
	LineF() {}
	LineF(CPoint p1, CPoint p2);
	LineF(CPoint p1, CPoint p2, int ID);
	bool  isInside(const CPoint& P) const;
	void Draw(CDC* dc) const;
};

