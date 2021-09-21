#include <math.h>
#include "stdafx.h"
#include "TriangleF.h"

IMPLEMENT_SERIAL(TriangleF, CObject, 1)

TriangleF::TriangleF(CPoint p1, CPoint p2) : RectangleF(p1, p2) {
	kind = 2;
}

TriangleF::TriangleF(CPoint p1, CPoint p2, int ID) : RectangleF(p1, p2, ID) {
	kind = 2;
}

void TriangleF::Draw(CDC* dc) const
{
	CBrush cb;
	cb.CreateSolidBrush(GetBGColor());
	CPen cp;
	cp.CreatePen(GetSWidth() > 0 ? GetSStyle() : PS_NULL,
		GetSWidth(), GetSColor());
	dc->SelectObject(cb);
	dc->SelectObject(cp);
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	CPoint vertices[3];
	vertices[0].x = p1.x + (p2.x - p1.x) / 2;
	vertices[0].y = p1.y;
	vertices[1].x = p1.x;
	vertices[1].y = p2.y;
	vertices[2].x = p2.x;
	vertices[2].y = p2.y;
	dc->Polygon(vertices, 3);
}

bool TriangleF::isInside(const CPoint& P) const {
	// skip calculating if not even in the bounding rectangle
	if (!Figure::isInside(P)) return false;

	// finding the number of intersections with the point's positive x parallel line
	CPoint A, B, C;
	A.x = getP1().x;
	A.y = getP2().y;
	B.x = getP1().x + (getP2().x - getP1().x) / 2;
	B.y = getP1().y;
	C = getP2();

	// x = (y - y1 + m * x1) / m
	int inter = 0;
	double Mab = (double)(A.y - B.y) / (A.x - B.x);
	if (((P.y - A.y + Mab * A.x) / Mab) > P.x) inter++;
	double Mbc = (double)(B.y - C.y) / (B.x - C.x);
	if (((P.y - B.y + Mbc * B.x) / Mbc) > P.x) inter++;

	return inter % 2 != 0; // if odd we're inside
}
