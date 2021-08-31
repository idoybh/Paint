
// MFCprojectDlg.h : header file
//

#pragma once

#include "Action.h"
#include "Figure.h"
#include "RectangleF.h"
#include "EllipseF.h"
#include "LineF.h"
#include "TriangleF.h"

// CMFCprojectDlg dialog
class CMFCprojectDlg : public CDialogEx
{
private:
	CPoint start, end;
	int futureFigureKind = 0; //Rectangle
	CTypedPtrArray<CObArray, Figure*> figs;
	CTypedPtrArray<CObArray, Action*> actions;
	CTypedPtrArray<CObArray, Action*> redoActions;

	bool isPressed = false;
	bool isErase = false;
	bool isEraseFreeFrm = false;
	bool isMove = false;
	Figure* movingFig = NULL;

	// controls
	CComboBox* m_ShapeSelect = NULL;
	CButton* m_EraseCB = NULL;
	CButton* m_EraseOBRadio = NULL;
	CButton* m_EraseFreeRadio = NULL;
	CButton* m_MoveCB = NULL;
	CStatic* m_CoordsTxt = NULL;
	CMFCColorButton* m_BGColorSelect = NULL;
	CMFCColorButton* m_SColorSelect = NULL;
	CComboBox* m_WidthSelect = NULL;
	// menu controls
	CMenu* m_EditMenu = NULL;

	// helper functions
	void AddAction(int, Figure);
	void RestoreFigure(Figure*);

// Construction
public:
	CMFCprojectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck2();
	// menu
	void OnFileNew();
	void OnFileSave();
	void OnFileLoad();
	void OnEditUndo();
	void OnEditRedo();
};
