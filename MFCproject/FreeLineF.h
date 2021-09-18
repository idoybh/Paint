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
	bool pointsInit = false;

	/**
	Updates the topmost, leftmost and rightmost, bottommost corners
	*/
	void UpdateCorners();

public:
	DECLARE_SERIAL(FreeLineF)   //!!! NO ";"  
	// must 4 serialization
	FreeLineF() { kind = 4; }

	/**
	Constructs a FreeLineF
	@param p1 the first point
	*/
	FreeLineF(CPoint p1);

	/**
	Constructs a FreeLineF, assigns a specific ID
	@param p1 the first point
	@param ID the ID
	*/
	FreeLineF(CPoint p1, int ID);

	/**
	Constructs a FreeLineF
	@param points a vector of all points
	*/
	FreeLineF(vector<CPoint> points);

	/**
	Constructs a FreeLineF, assigns a specific ID
	@param points a vector of all points
	@param ID the ID
	*/
	FreeLineF(vector<CPoint> points, int ID);

	FreeLineF(const FreeLineF& obj);

	void Serialize(CArchive& ar);

	void Draw(CDC* dc) const;

	/**
	Checks if a point is proximal to the line
	@param P the point to check
	@return true if near, false otherwise
	*/
	bool isInside(const CPoint& P) const;

	/**
	Moves the line by a diff
	@param dx the x axis diff
	@param dy the y axis diff
	*/
	void Shift(int dx, int dy);

	/**
	Redefines the Figure
	@param p1 new topmost leftmost point
	@param p2 new bottommost rightmost point
	*/
	void Redefine(CPoint p1, CPoint p2);

	/**
	Adds a new point to the line
	@param pnt the point to add
	*/
	void AddPoint(const CPoint& pnt);

	/**
	@return a vector of all points the line consists of
	*/
	vector<CPoint> getPoints() const;

	/**
	@return topmost, leftmost point
	*/
	CPoint getP1() const;

	/**
	@return bottommost, rightmost point
	*/
	CPoint getP2() const;
	
};
