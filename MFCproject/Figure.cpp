#include "stdafx.h"  //!!! 1st include
#include "Figure.h"

IMPLEMENT_SERIAL(Figure, CObject, 1)

Figure::Figure() : ID(figID++) {}

Figure::Figure(CPoint p1, CPoint p2) :
	P1(p1), P2(p2), ID(figID++) {}

Figure::Figure(CPoint p1, CPoint p2, int ID) :
	P1(p1), P2(p2), ID(ID) {}

Figure::Figure(const Figure& obj) :
	P1(obj.getP1()), P2(obj.getP2()),
	kind(obj.kind), BGColor(obj.BGColor),
	SColor(obj.SColor), PenWidth(obj.PenWidth),
	ID(obj.getID()) {
}

void Figure::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << P1;
		ar << P2;
		ar << ID;
		ar << kind;
		ar << BGColor;
		ar << SColor;
		ar << PenWidth;
	} else { // Loading, not storing
		ar >> P1;
		ar >> P2;
		ar >> ID;
		ar >> kind;
		ar >> BGColor;
		ar >> SColor;
		ar >> PenWidth;
	}
}

void Figure::Draw(CDC* dc) const {
	CBrush cb;
	cb.CreateSolidBrush(BGColor);
	CPen cp;
	cp.CreatePen(PS_SOLID, PenWidth, SColor);
	dc->SelectObject(cb);
	dc->SelectObject(cp);
	dc->Rectangle(P1.x, P1.y, P2.x, P2.y);
}

CPoint Figure::getP1() const {
	return P1;
}

CPoint Figure::getP2() const {
	return P2;
}

int Figure::getID() const {
	return ID;
}

int Figure::GetSWidth() const {
	return PenWidth;
}

COLORREF Figure::GetBGColor() const {
	return BGColor;
}

COLORREF Figure::GetSColor() const {
	return SColor;
}

void Figure::SetBGColor(const COLORREF c) {
	BGColor = c;
}

void Figure::SetSColor(const COLORREF c) {
	SColor = c;
}

void Figure::SetSWidth(const int w) {
	PenWidth = w;
}

int Figure::GetKind() const {
	return kind;
}

void Figure::Redefine(CPoint p1, CPoint p2) {
	P1 = p1;
	P2 = p2;
}

bool Figure::isInside(const CPoint& P) const {
	return (P1.x <= P.x && P.x <= P2.x || P1.x >= P.x && P.x >= P2.x) &&
		(P1.y <= P.y && P.y <= P2.y || P1.y >= P.y && P.y >= P2.y);
}

void Figure::Shift(int dx, int dy) {
	P1 = P1 + CPoint(dx, dy);
	P2 = P2 + CPoint(dx, dy);
}
