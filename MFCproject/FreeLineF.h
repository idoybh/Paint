#pragma once
#include <vector>
#include <math.h>
#include "Figure.h"

using std::vector;

class FreeLineF : public Figure {
private:
	vector<CPoint> points;
	CPoint topLeft;
	CPoint botRight;
	void UpdateCorners();

public:
	DECLARE_SERIAL(FreeLineF)   //!!! NO ";"  
	// must 4 serialization
	FreeLineF() {}
	FreeLineF(CPoint p1);
	FreeLineF(CPoint p1, int ID);
	FreeLineF(vector<CPoint> points);
	FreeLineF(vector<CPoint> points, int ID);
	FreeLineF(const FreeLineF& obj);
	void Serialize(CArchive& ar);
	void Draw(CDC* dc) const;
	bool isInside(const CPoint& P) const;
	void Shift(int dx, int dy);
	void AddPoint(const CPoint& pnt);
	vector<CPoint> getPoints() const;
	CPoint getTopLeft() const;
	CPoint getBotRight() const;
};
