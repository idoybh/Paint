#include "stdafx.h"
#include "ParallelogramF.h"

IMPLEMENT_SERIAL(ParallelogramF, CObject, 1)

ParallelogramF::ParallelogramF(CPoint p1, CPoint p2)
	: RectangleF(p1, p2) {
	kind = 5;
}

ParallelogramF::ParallelogramF(CPoint p1, CPoint p2, int ID)
	: RectangleF(p1, p2, ID) {
	kind = 5;
}

void ParallelogramF::Draw(CDC* dc) const {
	CBrush cb;
	cb.CreateSolidBrush(GetBGColor());
	CPen cp;
	cp.CreatePen(GetSWidth() > 0 ? GetSStyle() : PS_NULL,
		GetSWidth(), GetSColor());
	dc->SelectObject(cb);
	dc->SelectObject(cp);
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	CPoint vertices[4];
	vertices[0].x = p1.x;
	vertices[0].y = p1.y;
	vertices[1].x = p2.x - abs(p2.x - p1.x) / 4;
	vertices[1].y = p1.y;
	vertices[2].x = p2.x;
	vertices[2].y = p2.y;
	vertices[3].x = p1.x + abs(p2.x - p1.x) / 4;
	vertices[3].y = p2.y;
	dc->Polygon(vertices, 4);
}

bool ParallelogramF::isInside(const CPoint& P) const {
	// skip calculating if not even in the bounding rectangle
	if (!Figure::isInside(P)) return false;

	// finding the number of intersections with the point's positive x parallel line
	CPoint A, B, C, D;
	A = getP1();
	B.x = getP2().x - abs(getP2().x - getP1().x) / 4;
	B.y = getP1().y;
	C = getP2();
	D.x = getP1().x + abs(getP2().x - getP1().x) / 4;
	D.y = getP2().y;

	// x = (y - y1 + m * x1) / m
	int inter = 0;
	double Mad = (double)(A.y - D.y) / (A.x - D.x);
	if (((P.y - A.y + Mad * A.x) / Mad) > P.x) inter++;
	double Mbc = (double)(B.y - C.y) / (B.x - C.x);
	if (((P.y - B.y + Mbc * B.x) / Mbc) > P.x) inter++;

	return inter % 2 != 0; // if odd we're inside
}