//!! 15 b
#include "stdafx.h"
#include "EllipseF.h"

//!! 22 b
IMPLEMENT_SERIAL(EllipseF, CObject, 1)
//!! 22 e

EllipseF::EllipseF(CPoint p1, CPoint p2)
	:Figure(p1, p2)
{
}
void EllipseF::Draw(CDC* dc) const
{
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	dc->Ellipse(p1.x, p1.y, p2.x, p2.y);
}
//!! 15 e
