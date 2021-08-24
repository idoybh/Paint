#pragma once
#include "Figure.h"

class LineF : public Figure
{
	DECLARE_SERIAL(LineF)   //!!! NO ";"  
	public:
		//!! 22 b
		// must 4 serialization
		LineF() {}
		//!! 22 b
		LineF(CPoint p1, CPoint p2);
		void Draw(CDC* dc) const;
};

