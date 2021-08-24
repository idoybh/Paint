#include "stdafx.h"
#include "LineF.h"

IMPLEMENT_SERIAL(LineF, CObject, 1)

LineF::LineF(CPoint p1, CPoint p2) : Figure(p1, p2)
{

}

void LineF::Draw(CDC* dc) const
{
	CPoint p1 = getP1();
	CPoint p2 = getP2();
	dc->MoveTo(p1.x, p1.y);
	dc->LineTo(p2.x, p2.y);
}
