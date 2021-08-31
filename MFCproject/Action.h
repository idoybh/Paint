#pragma once
#include "Figure.h"

#define ACTION_KIND_DRAW 0
#define ACTION_KIND_ERASE 1
#define ACTION_KIND_MOVE 2
#define ACTION_KIND_TRANSFORM 3

class Action : public CObject
{
private:
	const int kind;
	Figure fig;
	
public:
	Action(int, Figure);
	int getKind() const;
	Figure getFigure() const;
};

