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
	cp.CreatePen(PS_SOLID, GetSWidth(), GetSColor());
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

	// caculating all relative spaces to P using Heron's formula
	CPoint A, B, C;
	A.x = getP1().x;
	A.y = getP2().y;
	B.x = getP1().x + (getP2().x - getP1().x) / 2;
	B.y = getP1().y;
	C = getP2();

	double BC = sqrt((C.x - B.x) * (C.x - B.x) + (C.y - B.y) * (C.y - B.y));
	double BA = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
	double AC = sqrt((C.x - A.x) * (C.x - A.x) + (C.y - A.y) * (C.y - A.y));

	double PB = sqrt((P.x - B.x) * (P.x - B.x) + (P.y - B.y) * (P.y - B.y));
	double PC = sqrt((P.x - C.x) * (P.x - C.x) + (P.y - C.y) * (P.y - C.y));
	double PA = sqrt((P.x - A.x) * (P.x - A.x) + (P.y - A.y) * (P.y - A.y));

	// S(ABC)
	double d0 = (BA + BC + AC) / 2;
	double ttlSpace = sqrt(d0 * (d0 - BA) * (d0 - BC) * (d0 - AC));

	// S(PBC)
	double d1 = (PB + PC + BC) / 2;
	double s1 = sqrt(d1 * (d1 - PB) * (d1 - PC) * (d1 - BC));

	// S(PBA)
	double d2 = (PB + PA + BA) / 2;
	double s2 = sqrt(d2 * (d2 - PB) * (d2 - PA) * (d2 - BA));

	// S(PAC)
	double d3 = (PA + PC + AC) / 2;
	double s3 = sqrt(d3 * (d3 - PA) * (d3 - PC) * (d3 - AC));

	// return true if the sum of all spaces = to the rectangle's space
	double diff = abs(ttlSpace - (s1 + s2 + s3));
	return diff <= 1; // allow some deviation
}
