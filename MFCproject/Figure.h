#pragma once
#include "stdafx.h"

#define FIGURE_KIND_RECTANGLE 0
#define FIGURE_KIND_ELLIPSE 1
#define FIGURE_KIND_TRIANGLE 2
#define FIGURE_KIND_LINE 3

static int figID = 1;

class Figure: public CObject {

	DECLARE_SERIAL(Figure)   //!!! NO ";"  

	const int ID;
	CPoint P1;
	CPoint P2;
	COLORREF BGColor = 0xFFFFFF;
	COLORREF SColor = 0x000000;
	int PenWidth = 1;

protected:
	int kind = 0;

public:
	// must 4 serialization
	Figure() : ID(figID++) { }

	Figure(CPoint p1, CPoint p2) :
		P1(p1), P2(p2), ID(figID++) { }

	Figure(CPoint p1, CPoint p2, int ID) :
		P1(p1), P2(p2), ID(ID) {
	}

	Figure(const Figure &obj) :
		P1(obj.getP1()), P2(obj.getP2()),
		kind(obj.kind), ID(obj.getID()) { }

	void Serialize(CArchive& ar);

	virtual void Draw(CDC* dc) const {
		CBrush cb;
		cb.CreateSolidBrush(BGColor);
		CPen cp;
		cp.CreatePen(PS_SOLID, PenWidth, SColor);
		dc->SelectObject(cb);
		dc->SelectObject(cp);
		dc->Rectangle(P1.x, P1.y, P2.x, P2.y);
	}

	CPoint getP1() const {
		return P1;
	}

	CPoint getP2() const {
		return P2;
	}

	int getID() const {
		return ID;
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

	int GetKind() const { return kind; }
	virtual void Redefine(CPoint p1, CPoint p2) { P1 = p1; P2 = p2; }
	virtual bool isInside(const CPoint &P) const;
	virtual void Shift(int dx, int dy);
};
