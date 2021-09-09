#include "stdafx.h"
#include "FreeLineF.h"

IMPLEMENT_SERIAL(FreeLineF, CObject, 1)

FreeLineF::FreeLineF(CPoint p1) {
	kind = 4;
}

FreeLineF::FreeLineF(CPoint p1, int ID) : Figure(NULL, NULL, ID) {
	kind = 4;
	points.push_back(p1);
	topLeft = botRight = p1;
	pointsInit = true;
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
	: Figure(obj) {
	kind = 4;
	points = obj.points;
	UpdateCorners();
}

void FreeLineF::Serialize(CArchive& ar) {
	Figure::Serialize(ar);
	if (ar.IsStoring()) {
		ar << (int)points.size();
		for (auto i = points.begin(); i != points.end(); ++i)
			ar << *i;
	} else { // loading
		int size;
		ar >> size;
		points.resize(size);
		for (int i = 0; i < size; i++)
			ar >> points[i];
		UpdateCorners();
	}
}

void FreeLineF::Draw(CDC* dc) const {
	CPen cp;
	cp.CreatePen(PS_SOLID, GetSWidth(), GetSColor());
	dc->SelectObject(cp);
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
	if (pnt.x < topLeft.x || !pointsInit)
		topLeft.x = pnt.x;
	if (pnt.y < topLeft.y || !pointsInit)
		topLeft.y = pnt.y;
	if (pnt.x > botRight.x || !pointsInit)
		botRight.x = pnt.x;
	if (pnt.y > botRight.y || !pointsInit)
		botRight.y = pnt.y;
	pointsInit = true;
}

vector<CPoint> FreeLineF::getPoints() const {
	return points;
}

CPoint FreeLineF::getP1() const {
	return topLeft;
}

CPoint FreeLineF::getP2() const {
	return botRight;
}

void FreeLineF::UpdateCorners() {
	if (points.empty()) return;
	CPoint tL = points[0];
	CPoint bR = points[0];
	for (auto i = points.begin(); i != points.end(); ++i) {
		CPoint curr = *i;
		if (curr.x < tL.x) tL.x = curr.x;
		if (curr.y < tL.y) tL.y = curr.y;
		if (curr.x > bR.x) bR.x = curr.x;
		if (curr.y > bR.y) bR.y = curr.y;
	}
	topLeft = tL;
	botRight = bR;
	pointsInit = true;
}
