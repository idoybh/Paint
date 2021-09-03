#include "stdafx.h"
#include "FreeLineF.h"

IMPLEMENT_SERIAL(FreeLineF, CObject, 1)

FreeLineF::FreeLineF(CPoint p1) : Figure(p1, p1) {
	kind = 4;
	points.push_back(p1);
	topLeft = botRight = p1;
}

FreeLineF::FreeLineF(CPoint p1, int ID) : Figure(p1, p1, ID) {
	kind = 4;
	points.push_back(p1);
	topLeft = botRight = p1;
}

FreeLineF::FreeLineF(vector<CPoint> points) {
	kind = 4;
	this->points = points;
	UpdateCorners();
}

FreeLineF::FreeLineF(vector<CPoint> points, int ID)
	: Figure(NULL, NULL, ID) {
	kind = 4;
	this->points = points;
	UpdateCorners();
}

FreeLineF::FreeLineF(const FreeLineF& obj)
	: Figure(NULL, NULL, obj.getID()) {
	kind = 4;
	points = obj.points;
}

void FreeLineF::Draw(CDC* dc) const {
	CPen cp;
	cp.CreatePen(PS_SOLID, GetSWidth(), GetSColor());
	dc->SelectObject(cp);
	bool from = true;
	CPoint prev = *points.begin();
	for (auto i = points.begin(); i != points.end(); ++i) {
		CPoint curr = *i;
		dc->MoveTo(prev.x, prev.y);
		dc->LineTo(curr.x, curr.y);
		prev = curr;
	}
}

bool FreeLineF::isInside(const CPoint& P) const {
	// save calculating if not even in the bounding rectangle
	CPoint P1 = topLeft;
	CPoint P2 = botRight;
	if (!(P1.x <= P.x && P.x <= P2.x || P1.x >= P.x && P.x >= P2.x) &&
		(P1.y <= P.y && P.y <= P2.y || P1.y >= P.y && P.y >= P2.y)) return false;

	for (auto i = points.begin(); i != points.end(); ++i) {
		CPoint curr = *i;
		double distance = sqrt((curr.x - P.x) * (curr.x - P.x)
			+ (curr.y - P.y) * (curr.y - P.y));
		if (distance < 13) return true;
	}
	return false;
}

void FreeLineF::Shift(int dx, int dy) {
	for (auto i = points.begin(); i != points.end(); ++i) {
		(*i).x += dx; (*i).y += dy;
	}
	topLeft.x += dx;
	topLeft.y += dy;
	botRight.x += dx;
	botRight.y += dy;
}

void FreeLineF::Redefine(CPoint p1, CPoint p2) {
	int dx = p1.x - topLeft.x;
	int dy = p1.y - topLeft.y;
	Shift(dx, dy);
}

void FreeLineF::AddPoint(const CPoint& pnt) {
	points.push_back(pnt);
	if (pnt.x < topLeft.x) topLeft.x = pnt.x;
	if (pnt.y < topLeft.y) topLeft.y = pnt.y;
	if (pnt.x > botRight.x) botRight.x = pnt.x;
	if (pnt.y > botRight.y) botRight.y = pnt.y;
}

CPoint FreeLineF::getP1() const {
	return topLeft;
}

CPoint FreeLineF::getP2() const {
	return botRight;
}

void FreeLineF::UpdateCorners() {
	CPoint tL = topLeft;
	CPoint bR = botRight;
	for (auto i = points.begin(); i != points.end(); ++i) {
		CPoint curr = *i;
		if (curr.x < tL.x) tL.x = curr.x;
		if (curr.y < tL.y) tL.y = curr.y;
		if (curr.x > bR.x) bR.x = curr.x;
		if (curr.y > bR.y) bR.y = curr.y;
	}
	topLeft = tL;
	botRight = bR;
}
