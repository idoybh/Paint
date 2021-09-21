#include "stdafx.h"
#include "Action.h"
#include "RectangleF.h"
#include "EllipseF.h"
#include "TriangleF.h"
#include "LineF.h"
#include "FreeLineF.h"
#include "ParallelogramF.h"

IMPLEMENT_SERIAL(Action, CObject, 2)

Action::Action(int kind, Figure* fig)
	: kind(kind) {
	// we need to store a deep copy.
	// storing in a pointer to achive proper polymorphism
	switch (fig->GetKind()) {
		default:
		case FIGURE_KIND_RECTANGLE:
			this->fig = (new RectangleF(*(RectangleF*)fig));
			break;
		case FIGURE_KIND_ELLIPSE:
			this->fig = (new EllipseF(*(EllipseF*)fig));
			break;
		case FIGURE_KIND_TRIANGLE:
			this->fig = (new TriangleF(*(TriangleF*)fig));
			break;
		case FIGURE_KIND_LINE:
			this->fig = (new LineF(*(LineF*)fig));
			break;
		case FIGURE_KIND_FREE_LINE:
			this->fig = (new FreeLineF(*(FreeLineF*)fig));
			break;
		case FIGURE_KIND_PARALLEL:
			this->fig = (new ParallelogramF(*(ParallelogramF*)fig));
			break;
	}
}

void Action::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << kind;
		ar << fig->GetKind();
	} else { // Loading, not storing
		ar >> kind;
		int figKind;
		ar >> figKind;
		switch (figKind) {
			case FIGURE_KIND_RECTANGLE:
				fig = new RectangleF();
				break;
			case FIGURE_KIND_ELLIPSE:
				fig = new EllipseF();
				break;
			case FIGURE_KIND_TRIANGLE:
				fig = new TriangleF();
				break;
			case FIGURE_KIND_LINE:
				fig = new LineF();
				break;
			case FIGURE_KIND_FREE_LINE:
				fig = new FreeLineF();
				break;
			case FIGURE_KIND_PARALLEL:
				fig = new ParallelogramF();
				break;
		}
	}
	fig->Serialize(ar);
}

int Action::getKind() const {
	return kind;
}

Figure* Action::getFigure() const {
	return fig;
}