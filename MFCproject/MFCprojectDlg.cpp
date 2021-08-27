
// MFCprojectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCproject.h"
#include "MFCprojectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCprojectDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCprojectDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(ID_FILE_NEW, &CMFCprojectDlg::OnFileNew)
	ON_BN_CLICKED(ID_FILE_SAVE, &CMFCprojectDlg::OnFileSave)
	ON_BN_CLICKED(ID_FILE_LOAD, &CMFCprojectDlg::OnFileLoad)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCprojectDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCprojectDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CMFCprojectDlg message handlers

BOOL CMFCprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CComboBox* cb = (CComboBox*) GetDlgItem(IDC_COMBO2);
	cb->SetCurSel(0);

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
HCURSOR CMFCprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCprojectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	start = point;
	isPressed = true;
	if (isErase) {
		for (int i = 0; i < figs.GetSize(); i++) {
			Figure* fig = figs.GetAt(i);
			if (fig->isInside(point)) {
				figs.RemoveAt(i);
				Invalidate();
				break;
			}
		}
	} else {
		switch (futureFigureKind) {
			case 0:
				figs.Add(new RectangleF(start, start));
				break;
			case 1:
				figs.Add(new EllipseF(start, start));
				break;
			case 2:
				figs.Add(new TriangleF(start, start));  
				break;
			case 3:
				figs.Add(new LineF(start, start));
				break;
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCprojectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isErase && isPressed) {
		isPressed = false;
	} else if (isPressed) {
		end = point;
		isPressed = false;
		figs[figs.GetSize() - 1]->Redefine(start, end);
		Invalidate(); //simulates the WM_PAINT message to redraw window
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCprojectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isPressed && isErase) {
		for (int i = 0; i < figs.GetSize(); i++) {
			Figure* fig = figs.GetAt(i);
			if (fig->isInside(point)) {
				figs.RemoveAt(i);
				Invalidate();
				break;
			}
		}
	} else if (isPressed) {
		end = point;
		figs[figs.GetSize() - 1]->Redefine(start, end);
		Invalidate(); //simulates the WM_PAINT message to redraw window
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCprojectDlg::OnCbnSelchangeCombo2() {
	CComboBox* cb = (CComboBox*) GetDlgItem(IDC_COMBO2);
	futureFigureKind = cb->GetCurSel();
}


void CMFCprojectDlg::OnBnClickedCheck1() {
	CButton* cb = (CButton*) GetDlgItem(IDC_CHECK1);
	isErase = cb->GetCheck() == BST_CHECKED;

	CButton* ccb1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton* ccb2 = (CButton*)GetDlgItem(IDC_RADIO2);
	if (isErase) {
		ccb1->EnableWindow(TRUE);
		ccb1->SetCheck(BST_CHECKED);
		ccb2->EnableWindow(TRUE);
		isEraseFreeFrm = false;
	} else {
		ccb1->EnableWindow(FALSE);
		ccb2->EnableWindow(FALSE);
	}
}

void CMFCprojectDlg::OnBnClickedRadio1()
{
	CButton* cb = (CButton*)GetDlgItem(IDC_RADIO2);
	isEraseFreeFrm = cb->GetCheck() == BST_CHECKED;
}

void CMFCprojectDlg::OnBnClickedRadio2()
{
	CButton* cb = (CButton*)GetDlgItem(IDC_RADIO2);
	isEraseFreeFrm = cb->GetCheck() == BST_CHECKED;
}

void CMFCprojectDlg::OnFileNew() {
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
		ar.Close();
		file.Close();
		Invalidate();
	}
}
