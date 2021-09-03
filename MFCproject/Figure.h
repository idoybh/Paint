#pragma once
#include <vector>
#include "stdafx.h"

#define FIGURE_KIND_RECTANGLE 0
#define FIGURE_KIND_ELLIPSE 1
#define FIGURE_KIND_TRIANGLE 2
#define FIGURE_KIND_LINE 3
#define FIGURE_KIND_FREE_LINE 4

using std::vector;

static int figID = 1;

class Figure: public CObject {

private:
	int ID;
	CPoint P1;
	CPoint P2;
	COLORREF BGColor = 0xFFFFFF;
	COLORREF SColor = 0x000000;
	int PenWidth = 1;

protected:
	int kind = 0;
	vector<CPoint> points;

public:
	DECLARE_SERIAL(Figure)   //!!! NO ";"  
	// must 4 serialization
	Figure();
	Figure(CPoint p1, CPoint p2);
	Figure(CPoint p1, CPoint p2, int ID);
	Figure(const Figure& obj);

	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const;
	virtual CPoint getP1() const;
	virtual CPoint getP2() const;
	int getID() const;
	int GetSWidth() const;
	COLORREF GetBGColor() const;
	COLORREF GetSColor() const;
	void SetBGColor(const COLORREF c);
	void SetSColor(const COLORREF c);
	void SetSWidth(const int w);
	int GetKind() const;
	virtual void Redefine(CPoint p1, CPoint p2);
	virtual bool isInside(const CPoint &P) const;
	virtual void Shift(int dx, int dy);
	virtual vector<CPoint> getPoints() const { return points; };
};
