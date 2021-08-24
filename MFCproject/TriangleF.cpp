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