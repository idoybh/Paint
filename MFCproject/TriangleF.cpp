#include <math.h>
#include "stdafx.h"
#include "TriangleF.h"

IMPLEMENT_SERIAL(TriangleF, CObject, 1)

TriangleF::TriangleF(CPoint p1, CPoint p2) : Figure(p1, p2)
{

}

void TriangleF::Draw(CDC* dc) const
{
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
	double ttlSpace = ((getP1().y - getP2().y) * (getP2().x - getP1().x)) / 2;
	// caculating all relative spaces to P
	CPoint A, B, C;
	A.x = getP1().x;
	A.y = getP2().y;
	B.x = getP1().x + (getP2().x - getP1().x) / 2;
	B.y = getP1().y;
	C = getP2();
	// S(PBC)
	double m1 = (B.y - C.y) / (B.x - C.x);
	double d1 = (abs(m1 * P.x + P.y - m1 * B.x + B.y)) / (sqrt(m1 * m1 + 1));
	double BC = sqrt((C.x - B.x) * (C.x - B.x) + (C.y - B.y) * (C.y - B.y));
	double s1 = (BC * d1) / 2;
	// S(PBA)
	double m2 = (B.y - A.y) / (B.x - A.x);
	double d2 = (abs(m2 * P.x + P.y - m2 * B.x + B.y)) / (sqrt(m2 * m2 + 1));
	double BA = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
	double s2 = (BA * d2) / 2;
	// S(PAC)
	double m3 = (A.y - C.y) / (A.x - C.x);
	double d3 = (abs(m3 * P.x + P.y - m3 * A.x + A.y)) / (sqrt(m3 * m3 + 1));
	double AC = sqrt((C.x - A.x) * (C.x - A.x) + (C.y - A.y) * (C.y - A.y));
	double s3 = (AC * d3) / 2;
	// return true if the sum of all spaces = to the rectangle's space
	return ttlSpace == s1 + s2 + s3;
}
