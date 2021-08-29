#pragma once
#include "stdafx.h"

class Figure: public CObject {

	DECLARE_SERIAL(Figure)   //!!! NO ";"  

	CPoint P1;
	CPoint P2;
	COLORREF BGColor = 0xFFFFFF;
	COLORREF SColor = 0x000000;
	int PenWidth = 1;

public:
	// must 4 serialization
	Figure() {}

	Figure(CPoint p1, CPoint p2):
		P1(p1), P2(p2)
	{

	}

	void Serialize(CArchive& ar);

	virtual void Draw(CDC *dc) const
	{
		CBrush cb(BGColor);
		cb.CreateSolidBrush(BGColor);
		CPen cp;
		cp.CreatePen(PS_SOLID, PenWidth, SColor);
		dc->SelectObject(cb);
		dc->SelectObject(cp);
		dc->Rectangle(P1.x, P1.y, P2.x, P2.y);
	}

	CPoint getP1() const 
	{ 
		return P1;
	}

	CPoint getP2() const
	{
		return P2;
	}

	void SetBGColor(const COLORREF c) {
		BGColor = c;
	}

	void SetSColor(const COLORREF c) {
		SColor = c;
	}

	void SetSWidth(const int w) {
		PenWidth = w;
	}

	virtual void Redefine(CPoint p1, CPoint p2) { P1 = p1; P2 = p2; }
	virtual bool isInside(const CPoint &P) const;
	virtual void Shift(int dx, int dy);
};
