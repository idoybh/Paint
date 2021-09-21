
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
#include "ParallelogramF.h"

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

	/**
	Draws a figure
	@param kind the figure kind
	@param p1 Top left corner
	@param p2 Bottom right corner
	*/
	void DrawFig(int, CPoint, CPoint);

	/**
	Draws a figure with a specific ID
	@param kind the figure kind
	@param p1 Top left corner
	@param p2 Bottom right corner
	@param ID The figure ID
	*/
	void DrawFig(int, CPoint, CPoint, int);

	/**
	Sets the figure style using the current selected controls
	*/
	void SetSelectedProps(Figure*);

	/**
	Adds an undo action, handles menu enablement
	*/
	void AddAction(int, Figure*);

	/**
	Restores a Figure
	@param fig A pointer to the restored Figure
	*/
	void RestoreFigure(Figure*);

	/**
	Re-enables drawing controls
	*/
	void EnableDrawing();

	/**
	Loads a file, handles control enablement
	*/
	void LoadFile(CString filename);

	/**
	@return the canvas' bounding rectangle
	*/
	CRect getCanvasRect() const;

	/**
	Checks if a point is inside the canvas
	@return true if inside, false otherwise
	*/
	bool isInsideCanvas(const CPoint&);

	/**
	Asks the user to save if there are unsaved changes see OnFileSave
	@return if saved or not needed will return IDYES, otherwise will return the dialog's result int - one of: IDNO or IDCANCEL
	*/
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
