#include "stdafx.h"  //!!! 1st include
#include "Figure.h"

//!! 22 b
IMPLEMENT_SERIAL(Figure, CObject, 1)
//!! 22 e

//!! 21 b
void Figure::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << P1;
		ar << P2;
	}
	else // Loading, not storing
	{
		ar >> P1;
		ar >> P2;
	}
}
//!! 21 e

bool Figure::isInside(const CPoint &P) const
{
	return (P1.x <= P.x && P.x <= P2.x || P1.x >= P.x && P.x >= P2.x) &&
		(P1.y <= P.y && P.y <= P2.y || P1.y >= P.y && P.y >= P2.y);
}
void Figure::Shift(int dx, int dy)
{
	P1 = P1 + CPoint(dx, dy);
	P2 = P2 + CPoint(dx, dy);
}
