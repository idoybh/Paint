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

	// caculating all relative spaces to P using Heron's formula
	CPoint A, B, C, D;
	A = getP1();
	B.x = getP2().x - abs(getP2().x - getP1().x) / 4;
	B.y = getP1().y;
	C = getP2();
	D.x = getP1().x + abs(getP2().x - getP1().x) / 4;
	D.y = getP2().y;

	double BC = sqrt((C.x - B.x) * (C.x - B.x) + (C.y - B.y) * (C.y - B.y)); // = AD
	double BA = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y)); // = DC

	double PB = sqrt((P.x - B.x) * (P.x - B.x) + (P.y - B.y) * (P.y - B.y));
	double PC = sqrt((P.x - C.x) * (P.x - C.x) + (P.y - C.y) * (P.y - C.y));
	double PA = sqrt((P.x - A.x) * (P.x - A.x) + (P.y - A.y) * (P.y - A.y));
	double PD = sqrt((P.x - D.x) * (P.x - D.x) + (P.y - D.y) * (P.y - D.y));

	// S(ABCD)
	double ttlSpace = abs(C.y - B.y) * BA;

	// S(PBC)
	double d = (PB + PC + BC) / 2;
	double s1 = sqrt(d * (d - PB) * (d - PC) * (d - BC));

	// S(PBA)
	d = (PB + PA + BA) / 2;
	double s2 = sqrt(d * (d - PB) * (d - PA) * (d - BA));

	// S(PAD)
	d = (PD + PA + BC) / 2;
	double s3 = sqrt(d * (d - PD) * (d - PA) * (d - BC));

	// S(PDC)
	d = (PD + PC + BA) / 2;
	double s4 = sqrt(d * (d - PD) * (d - PC) * (d - BA));

	// return true if the sum of all spaces = to the parallelogram's space
	double diff = abs(ttlSpace - (s1 + s2 + s3 + s4));
	return diff <= 1; // allow some deviation
}