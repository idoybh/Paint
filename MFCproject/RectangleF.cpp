#include "stdafx.h" // must be 1st
#include "RectangleF.h"

IMPLEMENT_SERIAL(RectangleF, CObject, 1)

RectangleF::RectangleF(CPoint p1, CPoint p2) 
	:Figure(p1,p2) {
	kind = 0;
}

RectangleF::RectangleF(CPoint p1, CPoint p2, int ID)
	: Figure(p1, p2, ID) {
	kind = 0;
}
