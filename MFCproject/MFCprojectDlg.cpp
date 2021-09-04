
// MFCprojectDlg.cpp : implementation file
//

#include <string.h>
#include "stdafx.h"
#include "MFCproject.h"
#include "MFCprojectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <sstream>

// CMFCprojectDlg dialog
CMFCprojectDlg::CMFCprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCprojectDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCprojectDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CMFCprojectDlg::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CMFCprojectDlg::OnBnClickedMfccolorbutton2)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCprojectDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMFCprojectDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CMFCprojectDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(ID_FILE_NEW, &CMFCprojectDlg::OnFileNew)
	ON_BN_CLICKED(ID_FILE_SAVE, &CMFCprojectDlg::OnFileSave)
	ON_BN_CLICKED(ID_FILE_LOAD, &CMFCprojectDlg::OnFileLoad)
	ON_BN_CLICKED(ID_EDIT_UNDO, &CMFCprojectDlg::OnEditUndo)
	ON_BN_CLICKED(ID_EDIT_REDO, &CMFCprojectDlg::OnEditRedo)
	ON_COMMAND(ID_FIGKIND_ERASE, &CMFCprojectDlg::OnFigkindErase)
	ON_COMMAND(ID_FIGKIND_TRANSFORM, &CMFCprojectDlg::OnFigkindTransform)
END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//controls
	m_ShapeSelect = (CComboBox*)GetDlgItem(IDC_COMBO2);
	m_ShapeSelect->SetCurSel(0);
	m_EraseCB = (CButton*)GetDlgItem(IDC_CHECK1);
	m_MoveCB = (CButton*)GetDlgItem(IDC_CHECK2);
	m_TransformCB = (CButton*)GetDlgItem(IDC_CHECK3);
	m_CoordsTxt = (CStatic*)GetDlgItem(IDC_STATIC2);
	m_BGColorSelect = (CMFCColorButton*)GetDlgItem(IDC_MFCCOLORBUTTON1);
	m_BGColorSelect->SetColor(0xFFFFFF);
	m_SColorSelect = (CMFCColorButton*)GetDlgItem(IDC_MFCCOLORBUTTON2);
	m_SColorSelect->SetColor(0x000000);
	m_WidthSelect = (CComboBox*)GetDlgItem(IDC_COMBO3);
	m_WidthSelect->SetCurSel(1);
	// menu
	m_EditMenu = GetMenu()->GetSubMenu(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		for (int i = 0; i < figs.GetSize(); i++)
			figs[i]->Draw(&dc);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCprojectDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCprojectDlg::OnRButtonDown(UINT nFlags, CPoint point) {
	for (int i = figs.GetSize() - 1; i >= 0; i--) {
		Figure* fig = figs.GetAt(i);
		if (fig->isInside(point)) {
			// open up context menu for the current figure
			contextFigIndex = i;
			CMenu menu;
			menu.LoadMenuW(IDR_MENU2);
			CMenu* pPopup = menu.GetSubMenu(0);
			ClientToScreen(&point);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			break;
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (isInsideCanvas(point)) {
		start = point;
		isPressed = true;
		switch (futureActionKind) {
			default:
			case ACTION_KIND_DRAW:
				DrawFig(futureFigureKind, start, start);
				break;
			case ACTION_KIND_ERASE:
				for (int i = figs.GetSize() - 1; i >= 0; i--) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						AddAction(ACTION_KIND_ERASE, fig);
						figs.RemoveAt(i);
						Invalidate();
						break;
					}
				}
				break;
			case ACTION_KIND_MOVE:
				for (int i = 0; i < figs.GetSize(); i++) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						movingFig = fig;
						AddAction(ACTION_KIND_MOVE, movingFig);
						break;
					}
				}
				break;
			case ACTION_KIND_TRANSFORM:
				for (int i = 0; i < figs.GetSize(); i++) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						AddAction(ACTION_KIND_TRANSFORM, figs.GetAt(i));
						fig->SetBGColor(m_BGColorSelect->GetColor());
						fig->SetSColor(m_SColorSelect->GetColor());
						fig->SetSWidth(m_WidthSelect->GetCurSel());
						Invalidate();
						break;
					}
				}
				break;
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isPressed) {
		isPressed = false;
		switch (futureActionKind) {
			default:
			case ACTION_KIND_DRAW:
				if (futureFigureKind == FIGURE_KIND_FREE_LINE) {
					AddAction(ACTION_KIND_DRAW, figs[figs.GetSize() - 1]);
					break;
				}
				end = point;
				figs[figs.GetSize() - 1]->Redefine(start, end);
				Invalidate(); //simulates the WM_PAINT message to redraw window
				AddAction(ACTION_KIND_DRAW, figs[figs.GetSize() - 1]);
				break;
			case ACTION_KIND_ERASE:
				break;
			case ACTION_KIND_MOVE:
				movingFig = NULL;
				break;
			case ACTION_KIND_TRANSFORM:
				break;
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	std::stringstream str;
	str << point.x << ":" << point.y;
	char* cstr = new char[20];
	strcpy(cstr, str.str().c_str());
	m_CoordsTxt->SetWindowText(CA2W(cstr));
	delete[] cstr;

	if (isPressed && isInsideCanvas(point)) {
		switch (futureActionKind) {
			default:
			case ACTION_KIND_DRAW:
				end = point;
				if (futureFigureKind != FIGURE_KIND_FREE_LINE)
					figs[figs.GetSize() - 1]->Redefine(start, end);
				else
					((FreeLineF*)figs[figs.GetSize() - 1])->AddPoint(end);
				Invalidate(); //simulates the WM_PAINT message to redraw window
				break;
			case ACTION_KIND_ERASE:
				for (int i = figs.GetSize() - 1; i >= 0; i--) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						AddAction(ACTION_KIND_ERASE, fig);
						figs.RemoveAt(i);
						Invalidate();
						break;
					}
				}
				break;
			case ACTION_KIND_MOVE:
				if (movingFig != NULL) {
					end = point;
					double deltaX = end.x - start.x;
					double deltaY = end.y - start.y;
					// avoid moving out of canvas
					CPoint fPTL = movingFig->getP1().x < movingFig->getP2().x ?
						movingFig->getP1() : movingFig->getP2();
					fPTL.x += deltaX; fPTL.y += deltaY;
					CPoint fPBR = movingFig->getP1().x < movingFig->getP2().x ?
						movingFig->getP2() : movingFig->getP1();
					fPBR.x += deltaX; fPBR.y += deltaY;
					if (!isInsideCanvas(fPTL) || !isInsideCanvas(fPBR)) break;
					movingFig->Shift(deltaX, deltaY);
					start = end;
					Invalidate();
				}
				break;
			case ACTION_KIND_TRANSFORM:
				break;
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCprojectDlg::OnCbnSelchangeCombo2() {
	futureFigureKind = m_ShapeSelect->GetCurSel();
	m_TransformCB->SetCheck(BST_UNCHECKED);
	EnableDrawing();
}

void CMFCprojectDlg::OnCbnSelchangeCombo3() {
	if (futureActionKind != ACTION_KIND_TRANSFORM)
		EnableDrawing();
}

void CMFCprojectDlg::OnBnClickedMfccolorbutton1() {
	if (futureActionKind != ACTION_KIND_TRANSFORM)
		EnableDrawing();
}


void CMFCprojectDlg::OnBnClickedMfccolorbutton2() {
	if (futureActionKind != ACTION_KIND_TRANSFORM)
		EnableDrawing();
}

void CMFCprojectDlg::OnBnClickedCheck1() {
	bool checked = m_EraseCB->GetCheck() == BST_CHECKED;
	if (checked) {
		m_MoveCB->SetCheck(BST_UNCHECKED);
		m_TransformCB->SetCheck(BST_UNCHECKED);
		futureActionKind = ACTION_KIND_ERASE;
	} else {
		futureActionKind = ACTION_KIND_DRAW;
	}
}

void CMFCprojectDlg::OnBnClickedCheck2() {
	bool checked = m_MoveCB->GetCheck() == BST_CHECKED;
	if (checked) {
		m_EraseCB->SetCheck(BST_UNCHECKED);
		m_TransformCB->SetCheck(BST_UNCHECKED);
		futureActionKind = ACTION_KIND_MOVE;
	} else {
		futureActionKind = ACTION_KIND_DRAW;
	}
}

void CMFCprojectDlg::OnBnClickedCheck3() {
	bool checked = m_TransformCB->GetCheck() == BST_CHECKED;
	if (checked) {
		m_EraseCB->SetCheck(BST_UNCHECKED);
		m_MoveCB->SetCheck(BST_UNCHECKED);
		futureActionKind = ACTION_KIND_TRANSFORM;
	} else {
		futureActionKind = ACTION_KIND_DRAW;
	}
}

// menu

void CMFCprojectDlg::OnFileNew() {
	actions.RemoveAll();
	redoActions.RemoveAll();
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_DISABLED);
	figs.RemoveAll();
	Invalidate();
}

void CMFCprojectDlg::OnFileSave() {
	// FALSE to SAVE
	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figs.Serialize(ar);
		actions.Serialize(ar);
		redoActions.Serialize(ar);
		ar.Close();
		file.Close();
	}
}

void CMFCprojectDlg::OnFileLoad() {
	// TRUE to LOAD
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		actions.Serialize(ar);
		redoActions.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
		m_EditMenu->EnableMenuItem(ID_EDIT_UNDO,
			actions.IsEmpty() ? MF_DISABLED : MF_ENABLED);
		m_EditMenu->EnableMenuItem(ID_EDIT_REDO,
			redoActions.IsEmpty() ? MF_DISABLED : MF_ENABLED);
	}
}

void CMFCprojectDlg::OnEditUndo() {
	Action* act = actions.GetAt(actions.GetSize() - 1);
	Figure* fig = act->getFigure();
	switch (act->getKind()) {
		case ACTION_KIND_DRAW:
			for (int i = 0; i < figs.GetSize(); i++) {
				if (figs.GetAt(i)->getID() == fig->getID()) {
					figs.RemoveAt(i);
					break;
				}
			}
			redoActions.Add(act);
			break;
		case ACTION_KIND_ERASE:
			RestoreFigure(fig);
			redoActions.Add(new Action(ACTION_KIND_ERASE,
				figs.GetAt(figs.GetSize() - 1)));
			break;
		case ACTION_KIND_MOVE:
			for (int i = 0; i < figs.GetSize(); i++) {
				if (figs.GetAt(i)->getID() == fig->getID()) {
					redoActions.Add(new Action(ACTION_KIND_MOVE, figs.GetAt(i)));
					figs.GetAt(i)->Redefine(fig->getP1(), fig->getP2());
					break;
				}
			}
			break;
		case ACTION_KIND_TRANSFORM:
			for (int i = 0; i < figs.GetSize(); i++) {
				if (figs.GetAt(i)->getID() == fig->getID()) {
					redoActions.Add(new Action(ACTION_KIND_TRANSFORM, figs.GetAt(i)));
					figs.GetAt(i)->SetBGColor(fig->GetBGColor());
					figs.GetAt(i)->SetSColor(fig->GetSColor());
					figs.GetAt(i)->SetSWidth(fig->GetSWidth());
					break;
				}
			}
			break;
	}
	Invalidate();
	actions.RemoveAt(actions.GetSize() - 1);
	if (actions.IsEmpty()) m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_ENABLED);
}

void CMFCprojectDlg::OnEditRedo() {
	Action* act = redoActions.GetAt(redoActions.GetSize() - 1);
	Figure* fig = act->getFigure();
	switch (act->getKind()) {
		case ACTION_KIND_DRAW:
			RestoreFigure(fig);
			actions.Add(new Action(ACTION_KIND_DRAW,
				figs.GetAt(figs.GetSize() - 1)));
			break;
		case ACTION_KIND_ERASE:
			for (int i = 0; i < figs.GetSize(); i++) {
				if (figs.GetAt(i)->getID() == fig->getID()) {
					figs.RemoveAt(i);
					break;
				}
			}
			actions.Add(act);
			break;
		case ACTION_KIND_MOVE:
			for (int i = 0; i < figs.GetSize(); i++) {
				if (figs.GetAt(i)->getID() == fig->getID()) {
					actions.Add(new Action(ACTION_KIND_MOVE, figs.GetAt(i)));
					figs.GetAt(i)->Redefine(fig->getP1(), fig->getP2());
					break;
				}
			}
			break;
		case ACTION_KIND_TRANSFORM:
			for (int i = 0; i < figs.GetSize(); i++) {
				if (figs.GetAt(i)->getID() == fig->getID()) {
					actions.Add(new Action(ACTION_KIND_TRANSFORM, figs.GetAt(i)));
					figs.GetAt(i)->SetBGColor(fig->GetBGColor());
					figs.GetAt(i)->SetSColor(fig->GetSColor());
					figs.GetAt(i)->SetSWidth(fig->GetSWidth());
					break;
				}
			}
			break;
	}
	Invalidate();
	redoActions.RemoveAt(redoActions.GetSize() - 1);
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_ENABLED);
	if (redoActions.IsEmpty()) m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_DISABLED);
}

// context menu

void CMFCprojectDlg::OnFigkindErase() {
	AddAction(ACTION_KIND_ERASE, figs.GetAt(contextFigIndex));
	figs.RemoveAt(contextFigIndex);
	Invalidate();
}

void CMFCprojectDlg::OnFigkindTransform() {
	AddAction(ACTION_KIND_TRANSFORM, figs.GetAt(contextFigIndex));
	figs.GetAt(contextFigIndex)->SetBGColor(m_BGColorSelect->GetColor());
	figs.GetAt(contextFigIndex)->SetSColor(m_SColorSelect->GetColor());
	figs.GetAt(contextFigIndex)->SetSWidth(m_WidthSelect->GetCurSel());
	Invalidate();
}

// helper functions

void CMFCprojectDlg::DrawFig(int kind, CPoint p1, CPoint p2) {
	switch (kind) {
		default:
		case FIGURE_KIND_RECTANGLE:
			figs.Add(new RectangleF(p1, p2));
			break;
		case FIGURE_KIND_ELLIPSE:
			figs.Add(new EllipseF(p1, p2));
			break;
		case FIGURE_KIND_TRIANGLE:
			figs.Add(new TriangleF(p1, p2));
			break;
		case FIGURE_KIND_LINE:
			figs.Add(new LineF(p1, p2));
			break;
		case FIGURE_KIND_FREE_LINE:
			figs.Add(new FreeLineF(p1));
	}
	figs[figs.GetSize() - 1]->SetBGColor(m_BGColorSelect->GetColor());
	figs[figs.GetSize() - 1]->SetSColor(m_SColorSelect->GetColor());
	figs[figs.GetSize() - 1]->SetSWidth(m_WidthSelect->GetCurSel());
}

void CMFCprojectDlg::DrawFig(int kind, CPoint p1, CPoint p2, int ID) {
	switch (kind) {
		default:
		case FIGURE_KIND_RECTANGLE:
			figs.Add(new RectangleF(p1, p2, ID));
			break;
		case FIGURE_KIND_ELLIPSE:
			figs.Add(new EllipseF(p1, p2, ID));
			break;
		case FIGURE_KIND_TRIANGLE:
			figs.Add(new TriangleF(p1, p2, ID));
			break;
		case FIGURE_KIND_LINE:
			figs.Add(new LineF(p1, p2, ID));
			break;
		case FIGURE_KIND_FREE_LINE:
			figs.Add(new FreeLineF(p1, ID));
	}
	figs[figs.GetSize() - 1]->SetBGColor(m_BGColorSelect->GetColor());
	figs[figs.GetSize() - 1]->SetSColor(m_SColorSelect->GetColor());
	figs[figs.GetSize() - 1]->SetSWidth(m_WidthSelect->GetCurSel());
}

void CMFCprojectDlg::AddAction(int kind, Figure* fig) {
	actions.Add(new Action(kind, fig));
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_ENABLED);
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_DISABLED);
	if (!redoActions.IsEmpty()) redoActions.RemoveAll();
}

void CMFCprojectDlg::RestoreFigure(Figure* fig) {
	switch (fig->GetKind()) {
		case FIGURE_KIND_RECTANGLE:
			figs.Add(new RectangleF(fig->getP1(), fig->getP2(), fig->getID()));
			break;
		case FIGURE_KIND_ELLIPSE:
			figs.Add(new EllipseF(fig->getP1(), fig->getP2(), fig->getID()));
			break;
		case FIGURE_KIND_TRIANGLE:
			figs.Add(new TriangleF(fig->getP1(), fig->getP2(), fig->getID()));
			break;
		case FIGURE_KIND_LINE:
			figs.Add(new LineF(fig->getP1(), fig->getP2(), fig->getID()));
			break;
		case FIGURE_KIND_FREE_LINE:
			figs.Add(new FreeLineF(((FreeLineF*) fig)->getPoints(), fig->getID()));
			break;
	}
	figs[figs.GetSize() - 1]->SetBGColor(fig->GetBGColor());
	figs[figs.GetSize() - 1]->SetSColor(fig->GetSColor());
	figs[figs.GetSize() - 1]->SetSWidth(fig->GetSWidth());
}

void CMFCprojectDlg::EnableDrawing() {
	m_EraseCB->SetCheck(BST_UNCHECKED);
	m_MoveCB->SetCheck(BST_UNCHECKED);
	futureActionKind = ACTION_KIND_DRAW;
}

bool CMFCprojectDlg::isInsideCanvas(const CPoint& pnt) {
	return (pnt.x >= 17 && pnt.y >= 80
		&& pnt.x <= 787 && pnt.y <= 480);
}
