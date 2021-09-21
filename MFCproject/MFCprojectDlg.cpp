
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
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCprojectDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCprojectDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCprojectDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCprojectDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CMFCprojectDlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCprojectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCprojectDlg::OnBnClickedButton2)
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
	ON_COMMAND(ID_FIGKIND_COPY, &CMFCprojectDlg::OnFigkindCopy)
	ON_COMMAND(ID_FIGKIND_PASTE, &CMFCprojectDlg::OnFigkindPaste)
END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DragAcceptFiles();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//controls
	m_ShapeSelect = (CComboBox*)GetDlgItem(IDC_COMBO2);
	m_ShapeSelect->SetCurSel(0);
	m_WidthSelect = (CComboBox*)GetDlgItem(IDC_COMBO3);
	m_WidthSelect->SetCurSel(1);
	m_StyleSelect = (CComboBox*)GetDlgItem(IDC_COMBO4);
	m_StyleSelect->SetCurSel(0);
	m_EraseCB = (CButton*)GetDlgItem(IDC_CHECK1);
	m_MoveCB = (CButton*)GetDlgItem(IDC_CHECK2);
	m_TransformCB = (CButton*)GetDlgItem(IDC_CHECK3);
	m_UndoBtn = (CButton*)GetDlgItem(IDC_BUTTON1);
	m_RedoBtn = (CButton*)GetDlgItem(IDC_BUTTON2);
	m_CoordsTxt = (CStatic*)GetDlgItem(IDC_STATIC2);
	m_BGColorSelect = (CMFCColorButton*)GetDlgItem(IDC_MFCCOLORBUTTON1);
	m_BGColorSelect->SetColor(0xFFFFFF);
	m_SColorSelect = (CMFCColorButton*)GetDlgItem(IDC_MFCCOLORBUTTON2);
	m_SColorSelect->SetColor(0x000000);
	// menu
	m_EditMenu = GetMenu()->GetSubMenu(1);

	m_UndoBtn->EnableWindow(FALSE);
	m_RedoBtn->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


BOOL CMFCprojectDlg::OnEraseBkgnd(CDC* dc) {
	if (!bgDone) {
		// only draw the default background once
		CDialogEx::OnEraseBkgnd(dc);
		bgDone = true;
	}
	// skip redrawing the background to avoid flickering
	return TRUE;
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
		CRect rect = getCanvasRect();

		CDC mDC; // memory CDC
		CBitmap mBitmap; // mamory CBitmap
		mDC.CreateCompatibleDC(&dc);
		mBitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
		CBitmap* oBitmap = (CBitmap*)mDC.SelectObject(&mBitmap);
		// draw the background
		mDC.FillSolidRect(0, 0, rect.right, rect.bottom, GetSysColor(COLOR_3DFACE));

		// draw to the memory dc
		for (int i = 0; i < figs.GetSize(); i++)
			figs[i]->Draw(&mDC);

		// copy to the on-screen dc bit by bit to avoid flickering
		dc.BitBlt(0, 0, rect.right, rect.bottom, &mDC, 0, 0, SRCCOPY);
		mDC.SelectObject(oBitmap);

		ReleaseDC(&dc);
		ReleaseDC(&mDC);

		// To avoid the control's flickering we call InvalidateRect() instead of Invalidate()

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCprojectDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCprojectDlg::OnDropFiles(HDROP drop) {
	CString filename;
	DWORD buffer = 0;
	UINT noFiles = DragQueryFile(drop, 0xFFFFFFFF, NULL, 0);
	// If more than one, only use the first
	if (noFiles > 0) {
		// Get the buffer size for the first filename
		buffer = DragQueryFile(drop, 0, NULL, 0);
		// Get path and name of the first file
		DragQueryFile(drop, 0, filename.GetBuffer(buffer + 1), buffer + 1);
		filename.ReleaseBuffer();
		
		if (AskSave() == IDCANCEL) return;
		LoadFile(filename);
	}
	DragFinish(drop);
}

void CMFCprojectDlg::OnCancel() {
	if (AskSave() == IDCANCEL) return;
	CDialog::OnCancel();
}

void CMFCprojectDlg::OnRButtonDown(UINT nFlags, CPoint point) {
	CMenu cmenu;
	cmenu.LoadMenuW(IDR_MENU2);
	CMenu* popup = cmenu.GetSubMenu(0);
	cursorP = point;
	bool found = false;
	for (INT_PTR i = figs.GetSize() - 1; i >= 0; i--) {
		Figure* fig = figs.GetAt(i);
		if (fig->isInside(point)) {
			// open up context menu for the current figure
			found = true;
			contextFigIndex = (int) i;
			ClientToScreen(&point);
			popup->EnableMenuItem(ID_FIGKIND_PASTE, copyFig != NULL ? MF_ENABLED : MF_DISABLED);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			break;
		}
	}
	if (!found && copyFig != NULL) {
		// open up context menu for paste only
		ClientToScreen(&point);
		popup->EnableMenuItem(ID_FIGKIND_ERASE, MF_DISABLED);
		popup->EnableMenuItem(ID_FIGKIND_TRANSFORM, MF_DISABLED);
		popup->EnableMenuItem(ID_FIGKIND_COPY, MF_DISABLED);
		popup->EnableMenuItem(ID_FIGKIND_PASTE, MF_ENABLED);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
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
				for (INT_PTR i = figs.GetSize() - 1; i >= 0; i--) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						AddAction(ACTION_KIND_ERASE, fig);
						figs.RemoveAt(i);
						InvalidateRect(getCanvasRect());
						break;
					}
				}
				break;
			case ACTION_KIND_MOVE:
				for (INT_PTR i = figs.GetSize() - 1; i >= 0; i--) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						movingFig = fig;
						AddAction(ACTION_KIND_MOVE, movingFig);
						break;
					}
				}
				break;
			case ACTION_KIND_TRANSFORM:
				for (INT_PTR i = figs.GetSize() - 1; i >= 0; i--) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						AddAction(ACTION_KIND_TRANSFORM, figs.GetAt(i));
						SetSelectedProps(figs.GetAt(i));
						InvalidateRect(getCanvasRect());
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
				InvalidateRect(getCanvasRect()); //simulates the WM_PAINT message to redraw window
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
				InvalidateRect(getCanvasRect()); //simulates the WM_PAINT message to redraw window
				break;
			case ACTION_KIND_ERASE:
				for (INT_PTR i = figs.GetSize() - 1; i >= 0; i--) {
					Figure* fig = figs.GetAt(i);
					if (fig->isInside(point)) {
						AddAction(ACTION_KIND_ERASE, fig);
						figs.RemoveAt(i);
						InvalidateRect(getCanvasRect());
						break;
					}
				}
				break;
			case ACTION_KIND_MOVE:
				if (movingFig != NULL) {
					end = point;
					long deltaX = end.x - start.x;
					long deltaY = end.y - start.y;
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
					InvalidateRect(getCanvasRect());
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
	if (futureFigureKind == FIGURE_KIND_FREE_LINE) {
		m_StyleSelect->SetCurSel(0);
		m_StyleSelect->EnableWindow(FALSE);
		m_BGColorSelect->EnableWindow(FALSE);
	} else {
		if (m_WidthSelect->GetCurSel() == 1)
			m_StyleSelect->EnableWindow(TRUE);
		m_BGColorSelect->EnableWindow(TRUE);
	}
}

void CMFCprojectDlg::OnCbnSelchangeCombo3() {
	if (futureActionKind != ACTION_KIND_TRANSFORM)
		EnableDrawing();
	if (m_WidthSelect->GetCurSel() != 1) {
		m_StyleSelect->SetCurSel(0);
		m_StyleSelect->EnableWindow(FALSE);
	} else if (futureFigureKind != FIGURE_KIND_FREE_LINE) {
		m_StyleSelect->EnableWindow(TRUE);
	}
}

void CMFCprojectDlg::OnCbnSelchangeCombo4() {
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

void CMFCprojectDlg::OnBnClickedButton1() {
	OnEditUndo();
}


void CMFCprojectDlg::OnBnClickedButton2() {
	OnEditRedo();
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
	if (AskSave() == IDCANCEL) return;
	actions.RemoveAll();
	redoActions.RemoveAll();
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_DISABLED);
	m_UndoBtn->EnableWindow(FALSE);
	m_RedoBtn->EnableWindow(FALSE);
	figs.RemoveAll();
	InvalidateRect(getCanvasRect());
	isSaved = true;
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
		isSaved = true;
	}
}

void CMFCprojectDlg::OnFileLoad() {
	if (AskSave() == IDCANCEL) return;
	// TRUE to LOAD
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		LoadFile(filename);
	}
}

void CMFCprojectDlg::OnEditUndo() {
	Action* act = actions.GetAt(actions.GetSize() - 1);
	Figure* fig = act->getFigure();
	isSaved = false;
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
					figs.GetAt(i)->SetSStyle(fig->GetSStyle());
					break;
				}
			}
			break;
	}
	InvalidateRect(getCanvasRect());
	actions.RemoveAt(actions.GetSize() - 1);
	if (actions.IsEmpty()) {
		m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
		m_UndoBtn->EnableWindow(FALSE);
	}
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_ENABLED);
	m_RedoBtn->EnableWindow(TRUE);
}

void CMFCprojectDlg::OnEditRedo() {
	Action* act = redoActions.GetAt(redoActions.GetSize() - 1);
	Figure* fig = act->getFigure();
	isSaved = false;
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
					figs.GetAt(i)->SetSStyle(fig->GetSStyle());
					break;
				}
			}
			break;
	}
	InvalidateRect(getCanvasRect());
	redoActions.RemoveAt(redoActions.GetSize() - 1);
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_ENABLED);
	m_UndoBtn->EnableWindow(TRUE);
	if (redoActions.IsEmpty()) {
		m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_DISABLED);
		m_RedoBtn->EnableWindow(FALSE);
	}
}

// context menu

void CMFCprojectDlg::OnFigkindErase() {
	AddAction(ACTION_KIND_ERASE, figs.GetAt(contextFigIndex));
	figs.RemoveAt(contextFigIndex);
	InvalidateRect(getCanvasRect());
}

void CMFCprojectDlg::OnFigkindTransform() {
	AddAction(ACTION_KIND_TRANSFORM, figs.GetAt(contextFigIndex));
	SetSelectedProps(figs.GetAt(contextFigIndex));
	InvalidateRect(getCanvasRect());
}

void CMFCprojectDlg::OnFigkindCopy() {
	copyFig = figs.GetAt(contextFigIndex);
}

void CMFCprojectDlg::OnFigkindPaste() {
	if (copyFig == NULL) return;
	switch (copyFig->GetKind()) {
		case FIGURE_KIND_RECTANGLE:
			figs.Add(new RectangleF(copyFig->getP1(), copyFig->getP2()));
			break;
		case FIGURE_KIND_ELLIPSE:
			figs.Add(new EllipseF(copyFig->getP1(), copyFig->getP2()));
			break;
		case FIGURE_KIND_TRIANGLE:
			figs.Add(new TriangleF(copyFig->getP1(), copyFig->getP2()));
			break;
		case FIGURE_KIND_LINE:
			figs.Add(new LineF(copyFig->getP1(), copyFig->getP2()));
			break;
		case FIGURE_KIND_FREE_LINE:
			figs.Add(new FreeLineF(((FreeLineF*)copyFig)->getPoints()));
			break;
		case FIGURE_KIND_PARALLEL:
			figs.Add(new ParallelogramF(copyFig->getP1(), copyFig->getP2()));
			break;
		case FIGURE_KIND_TRAPEZOID:
			figs.Add(new TrapezoidF(copyFig->getP1(), copyFig->getP2()));
			break;
	}
	// move it to the cursor position
	CPoint p1 = copyFig->getP1();
	CPoint p2 = copyFig->getP2();
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	p2.x = cursorP.x + dx; p2.y = cursorP.y + dy;
	if (!isInsideCanvas(p2)) { // stay inside canvas
		if (p2.x > 787) {
			dx = p2.x - 787;
			p2.x -= dx; cursorP.x -= dx;
		}
		if (p2.y > 480) {
			dy = p2.y - 480;
			p2.y -= dy; cursorP.y -= dy;
		}
	}
	figs[figs.GetSize() - 1]->Redefine(cursorP, p2);
	SetSelectedProps(figs[figs.GetSize() - 1]);

	AddAction(ACTION_KIND_DRAW, figs[figs.GetSize() - 1]);
	InvalidateRect(getCanvasRect());
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
			break;
		case FIGURE_KIND_PARALLEL:
			figs.Add(new ParallelogramF(p1, p2));
			break;
		case FIGURE_KIND_TRAPEZOID:
			figs.Add(new TrapezoidF(p1, p2));
			break;
	}
	SetSelectedProps(figs[figs.GetSize() - 1]);
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
			break;
		case FIGURE_KIND_PARALLEL:
			figs.Add(new ParallelogramF(p1, p2, ID));
			break;
		case FIGURE_KIND_TRAPEZOID:
			figs.Add(new TrapezoidF(p1, p2, ID));
			break;
	}
	SetSelectedProps(figs[figs.GetSize() - 1]);
}

void CMFCprojectDlg::SetSelectedProps(Figure* fig) {
	fig->SetBGColor(m_BGColorSelect->GetColor());
	fig->SetSColor(m_SColorSelect->GetColor());
	fig->SetSWidth(m_WidthSelect->GetCurSel());
	fig->SetSStyle(m_StyleSelect->GetCurSel());
}

void CMFCprojectDlg::AddAction(int kind, Figure* fig) {
	actions.Add(new Action(kind, fig));
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO, MF_ENABLED);
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO, MF_DISABLED);
	m_UndoBtn->EnableWindow(TRUE);
	m_RedoBtn->EnableWindow(FALSE);
	if (!redoActions.IsEmpty()) redoActions.RemoveAll();
	isSaved = false;
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
		case FIGURE_KIND_PARALLEL:
			figs.Add(new ParallelogramF(fig->getP1(), fig->getP2(), fig->getID()));
			break;
		case FIGURE_KIND_TRAPEZOID:
			figs.Add(new TrapezoidF(fig->getP1(), fig->getP2(), fig->getID()));
			break;
	}
	figs[figs.GetSize() - 1]->SetBGColor(fig->GetBGColor());
	figs[figs.GetSize() - 1]->SetSColor(fig->GetSColor());
	figs[figs.GetSize() - 1]->SetSWidth(fig->GetSWidth());
	figs[figs.GetSize() - 1]->SetSStyle(fig->GetSStyle());
}

void CMFCprojectDlg::EnableDrawing() {
	m_EraseCB->SetCheck(BST_UNCHECKED);
	m_MoveCB->SetCheck(BST_UNCHECKED);
	futureActionKind = ACTION_KIND_DRAW;
}

void CMFCprojectDlg::LoadFile(CString filename) {
	CFile file(filename, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	figs.Serialize(ar);
	actions.Serialize(ar);
	redoActions.Serialize(ar);
	ar.Close();
	file.Close();
	InvalidateRect(getCanvasRect());
	m_EditMenu->EnableMenuItem(ID_EDIT_UNDO,
		actions.IsEmpty() ? MF_DISABLED : MF_ENABLED);
	m_EditMenu->EnableMenuItem(ID_EDIT_REDO,
		redoActions.IsEmpty() ? MF_DISABLED : MF_ENABLED);
	m_UndoBtn->EnableWindow(!actions.IsEmpty());
	m_RedoBtn->EnableWindow(!redoActions.IsEmpty());
	isSaved = true;
}

CRect CMFCprojectDlg::getCanvasRect() const {
	// get the canvas' bounding rectangle 
	CWnd* canvas = GetDlgItem(IDC_STATIC6);
	CRect rect;
	canvas->GetWindowRect(rect);
	ScreenToClient(rect);
	// Add a border of 5px
	rect.TopLeft().x += 5;
	rect.TopLeft().y += 5;
	rect.BottomRight().x -= 5;
	rect.BottomRight().y -= 5;
	return rect;
}

bool CMFCprojectDlg::isInsideCanvas(const CPoint& pnt) {
	CRect rect = getCanvasRect();
	return (pnt.x >= rect.TopLeft().x && pnt.y >= rect.TopLeft().y
		&& pnt.x <= rect.BottomRight().x && pnt.y <= rect.BottomRight().y);
}

int CMFCprojectDlg::AskSave() {
	if (isSaved) return IDYES;
	CString msg(L"Unsaved changes detected.\nSave before continuing?");
	int res = AfxMessageBox(msg, MB_YESNOCANCEL, 0);
	switch (res) {
		default:
		case IDYES:
			OnFileSave();
			if (isSaved)
				return IDYES;
			else
				return IDCANCEL;
			break;
		case IDNO:
		case IDCANCEL:
			return res;
			break;
	}
}
