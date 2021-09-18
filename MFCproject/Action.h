#pragma once
#include "Figure.h"

#define ACTION_KIND_DRAW 0
#define ACTION_KIND_ERASE 1
#define ACTION_KIND_MOVE 2
#define ACTION_KIND_TRANSFORM 3

class Action : public CObject {
private:
	int kind;
	Figure* fig;

public:
	DECLARE_SERIAL(Action)
	Action() : kind(0), fig(NULL) { }; // for serialization

	/**
	Constructs a new Action
	@param kind the action kind
	@param a pointer to the Figure to store (a deep copy will be stored)
	*/
	Action(int kind, Figure* fig);

	void Serialize(CArchive& ar);

	/**
	@return action kind
	*/
	int getKind() const;

	/**
	@return a pointer to the stored figure
	*/
	Figure* getFigure() const;
};

