#pragma once
#include "stdafx.h"
class Figure: public CObject {
	//!! 21 b
	DECLARE_SERIAL(Figure)   //!!! NO ";"  
	//!! 21 e
	CPoint P1;
	CPoint P2;
public:
	//!! 22 b
	// must 4 serialization
	Figure() {}
	//!! 22 b

	//!! 21 b
	Figure(CPoint p1, CPoint p2):
		P1(p1), P2(p2)
	{
	}
	//!! 21 b
	void Serialize(CArchive& ar);
	//!! 21 e

	virtual void Draw(CDC *dc) const
	{
		dc->Rectangle(P1.x, P1.y, P2.x, P2.y);
	}
	//!! 15 b
	CPoint getP1() const 
	{ 
		return P1;
	}
	CPoint getP2() const
	{
		return P2;
	}
	//!! 15 e
	virtual void Redefine(CPoint p1, CPoint p2) { P1 = p1; P2 = p2; }
	virtual bool isInside(const CPoint &P) const;
	virtual void Shift(int dx, int dy);
};
