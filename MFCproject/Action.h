#pragma once
#include "Figure.h"

#define ACTION_KIND_DRAW 0
#define ACTION_KIND_ERASE 1
#define ACTION_KIND_MOVE 2
#define ACTION_KIND_TRANSFORM 3

class Action : public CObject {
private:
	int kind;
	Figure fig;

public:
	DECLARE_SERIAL(Action)
	Action() : kind(0) { }; // for serialization
	Action(int, Figure);
	void Serialize(CArchive& ar);
	int getKind() const;
	Figure getFigure() const;
};

