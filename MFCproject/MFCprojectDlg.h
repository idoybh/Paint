
// MFCprojectDlg.h : header file
//

#pragma once

#include "Action.h"
#include "Figure.h"
#include "RectangleF.h"
#include "EllipseF.h"
#include "LineF.h"
#include "TriangleF.h"
#include "FreeLineF.h"

// CMFCprojectDlg dialog
class CMFCprojectDlg : public CDialogEx
{
private:
	CPoint start, end, cursorP;
	int futureFigureKind = FIGURE_KIND_RECTANGLE;
	int futureActionKind = ACTION_KIND_DRAW;
	int contextFigIndex = -1;
	CTypedPtrArray<CObArray, Figure*> figs;
	CTypedPtrArray<CObArray, Action*> actions;
	CTypedPtrArray<CObArray, Action*> redoActions;

	bool isPressed = false;
	bool isSaved = true;
	bool bgDone = false;
	Figure* movingFig = NULL;
	Figure* copyFig = NULL;

	// controls
	CComboBox* m_ShapeSelect = NULL;
	CComboBox* m_WidthSelect = NULL;
	CComboBox* m_StyleSelect = NULL;
	CButton* m_EraseCB = NULL;
	CButton* m_MoveCB = NULL;
	CButton* m_TransformCB = NULL;
	CButton* m_UndoBtn = NULL;
	CButton* m_RedoBtn = NULL;
	CStatic* m_CoordsTxt = NULL;
	CMFCColorButton* m_BGColorSelect = NULL;
	CMFCColorButton* m_SColorSelect = NULL;
	// menu controls
	CMenu* m_EditMenu = NULL;

	// helper functions
	void DrawFig(int, CPoint, CPoint);
	void DrawFig(int, CPoint, CPoint, int);
	void SetSelectedProps(Figure*);
	void AddAction(int, Figure*);
	void RestoreFigure(Figure*);
	void EnableDrawing();
	void LoadFile(CString filename);
	CRect getCanvasRect() const;
	bool isInsideCanvas(const CPoint&);
	int AskSave();

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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedCheck3();
	// menu
	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	// context menu
	afx_msg void OnFigkindErase();
	afx_msg void OnFigkindTransform();
	afx_msg void OnFigkindCopy();
	afx_msg void OnFigkindPaste();
	afx_msg void OnCbnSelchangeCombo4();
};
