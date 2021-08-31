#include "stdafx.h"
#include "Action.h"

IMPLEMENT_SERIAL(Action, CObject, 1)

Action::Action(int kind, Figure fig)
	: kind(kind), fig(fig) { }

void Action::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << kind;
		fig.Serialize(ar);
	} else { // Loading, not storing
		ar >> kind;
		fig.Serialize(ar);
	}
}

int Action::getKind() const {
	return kind;
}

Figure Action::getFigure() const {
	return fig;
}