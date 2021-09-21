#pragma once
#include <vector>
#include "stdafx.h"

#define FIGURE_KIND_RECTANGLE 0
#define FIGURE_KIND_ELLIPSE 1
#define FIGURE_KIND_TRIANGLE 2
#define FIGURE_KIND_LINE 3
#define FIGURE_KIND_FREE_LINE 4
#define FIGURE_KIND_PARALLEL 5

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
	int PenStyle = PS_SOLID;

protected:
	int kind = 0;

public:
	DECLARE_SERIAL(Figure)   //!!! NO ";"  
	Figure(); // must 4 serialization

	/**
	Constructs a figure from 2 points
	@param p1 top left corner
	@param p2 bottom right corner
	*/
	Figure(CPoint p1, CPoint p2);

	/**
	Constructs a figure from 2 points, assigns specific ID
	@param p1 top left corner
	@param p2 bottom right corner
	@param ID the designated ID
	*/
	Figure(CPoint p1, CPoint p2, int ID);

	Figure(const Figure& obj);

	virtual void Serialize(CArchive& ar);

	virtual void Draw(CDC* dc) const;

	/**
	@return top left corner
	*/
	virtual CPoint getP1() const;

	/**
	@return bottom right corner
	*/
	virtual CPoint getP2() const;

	int getID() const;

	/**
	@return border width
	*/
	int GetSWidth() const;

	/**
	@return pen stroke style
	*/
	int GetSStyle() const;

	/**
	@return solid fill color
	*/
	COLORREF GetBGColor() const;

	/**
	@return border color
	*/
	COLORREF GetSColor() const;

	/**
	@param c new solid fill color
	*/
	void SetBGColor(const COLORREF c);

	/**
	@param c new border color
	*/
	void SetSColor(const COLORREF c);

	/**
	@param w new border width 
	*/
	void SetSWidth(const int w);

	/**
	@param s new border style
	*/
	void SetSStyle(const int s);

	int GetKind() const;

	/**
	Redefines the Figure
	@param p1 new top left corner
	@param p2 new bottom right corner
	*/
	virtual void Redefine(CPoint p1, CPoint p2);

	/**
	Checks if a point is inside the figure
	@param P the point to check
	@return true if inside, false otherwise
	*/
	virtual bool isInside(const CPoint &P) const;

	/**
	Moves the figure by a diff
	@param dx the x axis diff
	@param dy the y axis diff
	*/
	virtual void Shift(int dx, int dy);
};
