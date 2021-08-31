#include "stdafx.h"
#include "Action.h"

Action::Action(int kind, Figure fig)
	: kind(kind), fig(fig) { }

int Action::getKind() const {
	return kind;
}

Figure Action::getFigure() const {
	return fig;
}