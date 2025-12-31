// MyListCtrl.h: interface for the CMyListCtrl class.

#if !defined(AFX_MYLISTCTRL_H__97CE1A9D_7F61_472D_A2D9_C9A02E3165EA__INCLUDED_)
#define AFX_MYLISTCTRL_H__97CE1A9D_7F61_472D_A2D9_C9A02E3165EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyDialog.h"

class CMyMemDC : public CDC
{
public:
	CMyMemDC(CDC *pDC, LPRECT pRect=NULL, BOOL bBg=FALSE);
	virtual ~CMyMemDC();
	CBitmap	*GetBitmap();
private:
	CBitmap	 m_MemBM;
	CBitmap	*m_pOldBM;
	CDC		*m_pDC;
	CRect	 m_rect;
	BOOL	 m_bMemDC;
};

class CMyTime : public CTime
{
public:
	CMyTime(CTime &aTime);
	CMyTime(int dwTime=-1);
	virtual ~CMyTime();
	CString FormatTMString(int nType=0) ;
	int GetDaySeconds() ;
	int GetDayMinutes() ;
	void SetTime(int nSeconds=-1) ;
	TCHAR *FormatTM(int nType) ;

private:
	BOOL m_bCreated ;
	CTime *m_pTime  ;
};

class CMyProgressCtrl : public CProgressCtrl
{
public:
	CMyProgressCtrl();
	virtual ~CMyProgressCtrl();

	void SetMyProgress(int nMyPos = 0, LPCTSTR lpszMyText=NULL) ;
	void SetCtrlColor(COLORREF clr1,COLORREF clr2,DWORD dwType=0) ;
	static void SetDefColors(DWORD dwClrBK, DWORD dwClrPG, DWORD dwClrTxt);
	static void SetDefPictures(LPCTSTR lpszBK, LPCTSTR lpszPG);

private:
	CString  m_strMyText ;
	COLORREF m_clrBK1 ;
	COLORREF m_clrBK2 ;
	COLORREF m_clrTxt ;
	COLORREF m_clrPR1 ;
	COLORREF m_clrPR2 ;
	COLORREF m_clrErr ;
	CString  m_strPicBK;
	CString  m_strPicPG;

	BOOL m_bError ;

public:
	//{{AFX_VIRTUAL(CMyProgressCtrl)
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CMyProgressCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

class CMySliderCtrl: public CSliderCtrl
{
	DECLARE_DYNAMIC(CMySliderCtrl)
public:
	CMySliderCtrl();
	virtual~CMySliderCtrl();
	virtual void SetPos(int nPos) ;
	virtual int  GetPos() ;
	void SetReadOnly(BOOL bSet=TRUE) ;

	CString  m_strPicBK;
	CString  m_strPicPG;
	CString  m_strPicTH;
	COLORREF m_clrBK;
	COLORREF m_clrPG;
	COLORREF m_clrTH;
	int      m_nBarH ;
	int      m_nType ;
	
	static void SetDefColors(DWORD dwClrBK, DWORD dwClrPG, DWORD dwClrTH);
	static void SetDefPictures(LPCTSTR lpszBK, LPCTSTR lpszPG, LPCTSTR lpszTH);
	static void SetDefProgBarType(int nType=0);
	
private:
	int  m_nPos ;
	BOOL m_bMouseDown;
	BOOL m_bMouseIn;
	BOOL m_bReadOnly ;
	BOOL m_bHoriMode ;
	
	virtual BOOL PreTranslateMessage(MSG *pMsg);	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP();
};


class  CMyHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CMyHeaderCtrl)

public:
	CMyHeaderCtrl();
	virtual ~CMyHeaderCtrl();

	int m_nHeadHeight;   //表头高度，这是倍数,
	int m_nFontSize;     //字体高度
	COLORREF m_clrText;
	COLORREF m_clrBk1;
	COLORREF m_clrBk2;
	COLORREF m_clrGrid;
	BOOL     m_bTransParent ;
	BOOL     m_bShowGrid ;
	CString  m_strIcon ;
protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

class CMyListCtrlMini
{
public:
	CMyListCtrlMini(CListCtrl *pListCtrl);
	virtual ~CMyListCtrlMini();

public:
	__int64 GetItemInt(int nItem,int nSubItem);
	void    SetItemInt(int nItem,int nSubItem,__int64 nValue);
	float   GetItemFloat(int nItem,int nSubItem);
	void    SetItemFloat(int nItem,int nSubItem,float fValue,DWORD dwFixed=6);
	double  GetItemDouble(int nItem,int nSubItem);
	void    SetItemDouble(int nItem,int nSubItem,double dbValue,DWORD dwFixed=15);
	int     FindItemText(LPCTSTR lpszText,DWORD dwFindMask=0,int nFromItem=0,int nCol=-1) ;
private:
	CListCtrl *m_pListCtrl ;
};


class CMyListBox : public CListBox
{
	DECLARE_DYNAMIC(CMyListBox)
public:
	CMyListBox();
	virtual~CMyListBox();

	void SetAllItemsHeight(int nHeight) ;
	void SetActiveItem(int nItem);
	void SetFontSize(int nSize, BOOL bBold = FALSE, BOOL bItalic = FALSE);
	void SetItemColor(COLORREF clrBK1,COLORREF clrBK2,COLORREF clrTxt,DWORD dwType=0,BOOL bGradH=TRUE) ;//0 Nor 1 Hit 2 Sel
	void SetLeftMargin(int nMargin) ;
	void SetTransParent(BOOL bTrans=FALSE) ;
	void SetBackImage(LPCTSTR lpszFile) ;
	void SetImageList(CImageList *pImageList) ;
	void SetRightAlign(BOOL bSet=TRUE) ;
	void SetShowFocus(BOOL bShow=TRUE) ;
	void SetItemBKImage(LPCTSTR lpszNorBKImage=NULL,LPCTSTR lpszSelBKImage=NULL) ;

private:
	CFont *m_pFont       ;
	int   m_nHitItem     ;
	int   m_nSelItem     ;
	BOOL  m_bMouseDown   ;
	int   m_nGenHeight   ;
	int   m_nLeftMargin  ;
	BOOL  m_bTransParent ;
	BOOL  m_bRightAlign  ;
	BOOL  m_bShowFocus   ;
	CImageList *m_pImageList ;
	CString m_strItemNorBKImage ;
	CString m_strItemSelBKImage ;

	CString  m_strImgFile ;
	COLORREF m_clrListBK1 ;
	COLORREF m_clrListBK2 ;
	BOOL     m_bListGrdH  ;

	COLORREF m_clrNorTxt ;
	COLORREF m_clrNorBK1 ;
	COLORREF m_clrNorBK2 ;
	BOOL     m_bNorGrdH  ;

	COLORREF m_clrHitTxt ;
	COLORREF m_clrHitBK1 ;
	COLORREF m_clrHitBK2 ;
	BOOL     m_bHitGrdH  ;

	COLORREF m_clrSelTxt ;
	COLORREF m_clrSelBK1 ;
	COLORREF m_clrSelBK2 ;
	BOOL     m_bSelGrdH  ;

private:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void PreSubclassWindow();

protected:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	
	DECLARE_MESSAGE_MAP()
};

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)
public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

public:
	void SetHeaderHeight(int nHeight);                  //设置表头高度
	void SetHeaderFontSize(int nFontSize);              //设置表头字体大小
	void SetHeaderTextColor(COLORREF color);
	void SetHeaderAdjust(BOOL bEnable=TRUE);
	void SetRowHeight(int nHeight);                     //设置行高
	void SetHeaderText(int nCol,LPCTSTR lpszText) ;
	BOOL SelectItem(int nItem,BOOL bSel=TRUE) ;
	void SwapItem(int nItem1, int nItem2, int nFromCol=0);
	
	void SetItemBkColor(int nItem,int nCol,COLORREF color);//设置Item背景颜色
	void SetItemTextColor(int nItem,int nCol,COLORREF color);
	DWORD GetItemBkColor(int nItem,int nCol);
	DWORD GetItemTextColor(int nItem,int nCol);

	void SetDisableColor(COLORREF clrDisBK,COLORREF clrDisTxt);
	BOOL SetTextColor(COLORREF cr);
	void SetBkColorEx(COLORREF color1,COLORREF color2); //设置背景颜色
	void SetActColor(COLORREF color1,COLORREF color2);  //设置背景颜色
	void SelectAllItems(int nAction=1) ;      //1 全选  2 全不选 3 反选
	void CheckedtAllItems(int nAction=1) ;    //1 全选  2 全不选 3 反选
	BOOL IsSelected(int nItem) ;
	void SetBkImage(LPCTSTR lpszBkImgFile) ;
	void SetCheckBoxStyle(BOOL bSet=TRUE) ;
	void SetGridLineStyle(BOOL bSet=TRUE) ;
	void SetEvenRowColor(BOOL bEnableEvenRowColor,COLORREF clkEvenRowBk=0xFFFFFF,COLORREF clkEvenRowTxt=0);
	void SetFillLastCol(BOOL bToFillCol=TRUE,int nInterVal=5000) ;
	void SetDrawFocus(BOOL bSetFlag=TRUE) ;
	void SetTextEllipsis(BOOL bTxtElliPsis=TRUE);
	void DoFillLastCol() ;
	void SetItemIcon(int nItem, int nIconIndex);
	void SetItemImage(int nItem, int nCol,LPCTSTR lpszImage,DWORD dwAlign=1,int nMargin=0,int nOffset=0);
	void*GetItemImage(int nItem, int nCol);
	void SetShowTip(BOOL bShowTip) ;
	void SetTransParent(BOOL bToSet=TRUE) ;
	void SetMarkedItem(int nItem=-1) ;
	void SetTrackMode(BOOL bTrack=TRUE) ;
	void SetMarkedItemColor(COLORREF clrMK1,COLORREF clrMK2,COLORREF clrTxt) ;
	void SetPercentCol(int nCol,BOOL bToSet=TRUE);
	void SetCheckBoxCol(int nCol,BOOL bToSet=TRUE);
	void SetShowTypeCol(int nCol,int nType=0);
	void SetPercentColor(COLORREF clrBK,COLORREF clrPrg,COLORREF clrTxt);
	void SetItemIconI(int nItem,int nCol,int nIco,CImageList *pImg=NULL,int nAlign=0,int nOffset=0) ;
	void SetItemIconF(int nItem,int nCol,LPCTSTR lpszImgFile=NULL,int nAlign=0,int nOffset=0,int nPosX=0,int nPosY=0,int nW=-1,int nH=-1) ;
	void SetItemCheck(int nItem,int nCol,int nChecked=1) ;
	void SetItemReadOnly(int nItem,int nCol,BOOL bSet=TRUE) ;
	BOOL GetItemReadOnly(int nItem,int nCol) ;
	void SetItemDisable(int nItem,int nCol,BOOL bSet=TRUE) ;
	BOOL GetItemDisable(int nItem,int nCol) ;
	BOOL GetItemCheck(int nItem,int nCol) ;
	void SetItemClickNotify(DWORD wParam=CMD_LISTCTRL_COLCLK) ;
	void SetItemDbClkNotify(DWORD wParam=CMD_LISTCTRL_COLDCK) ;
	void SetItemTxtEdNotify(DWORD wParam=CMD_LISTCTRL_COLTXT) ;
	void SetItemHitedNotify(DWORD wParam=CMD_LISTCTRL_COLHIT) ;
	void SetItemFoucsCell(BOOL bSet=TRUE) ;
	void SetEditShowFullSel(BOOL bFullSel=TRUE) ;
	void ShowEdit() ;
	void ShowCombox(LPCTSTR *lpszStrings=NULL,BOOL bBuildListOnly=FALSE) ;
	int  GetComboxSel() ;
	void* GetCombox() ;
	void* GetEdit() ;
	void SetCombox(void *pCmb) ;
	void SetEdit(void *pEdit) ;
	void SetReadOnly(BOOL bToSet=TRUE) ;
	int  GetClickItem() ;
	int  GetClickSubItem() ;
	int  GetHitItem() ;
	int  GetHitSubItem() ;

	void Empty() ;
	void EmptyCol(int nCol=0,int nBegin=0,int nEnd=-1) ;
	void EmptyRow(int nRow=0,int nBegin=0,int nEnd=-1) ;
	void Fill(int nRows=10) ;
	void FillCol(int nCol,const CStringArray&arrVals) ;
	void FillRow(int nRow,const CStringArray&arrVals) ;
	void FillCol(int nCol,LPCTSTR *lpszVals,int nCount) ;
	void FillRow(int nRow,LPCTSTR *lpszVals,int nCount) ;

	void FillCol(int nCol,const CArray<int,int>&arrInts);
	void FillCol(int nCol,const CArray<double,double>&arrDoubles,DWORD dwFixed=15);
	void FillCol(int nCol,const CArray<float,float>&arrDoubles,DWORD dwFixed=6);
	void FillCol(int nCol,const int *pIntVals,int nCount=-1);
	void FillCol(int nCol,const double *pDoubleVals,int nCount=-1,DWORD dwFixed=15);
	void FillCol(int nCol,const float *pFloatVals,int nCount=-1,DWORD dwFixed=6);

	void FillRow(int nRow,const CArray<int,int>&arrInts);
	void FillRow(int nRow,const CArray<double,double>&arrDoubles,DWORD dwFixed=15);
	void FillRow(int nRow,const CArray<float,float>&arFloats,DWORD dwFixed=6);
	void FillRow(int nRow,const int *pIntVals,int nCount=-1);
	void FillRow(int nRow,const double *pDoubleVals,int nCount=-1,DWORD dwFixed=15);
	void FillRow(int nRow,const float *pFloatVals,int nCount=-1,DWORD dwFixed=6);

	int  GetCol(int nCol,CStringArray&arrVals) ;
	int  GetRow(int nRow,CStringArray&arrVals) ;
	void SetGridColor(DWORD dwColor=0);
	void SetGridWidth(DWORD dwWidth=1);

	void DoColumOrder(int nCol=0,int nBegin=1,int nFmtLen=1,LPCTSTR lpszPre=NULL,LPCTSTR lpszSub=NULL) ;
	void SetOrderColum(int nCol=0,LPCTSTR lpszPre=NULL,LPCTSTR lpszSub=NULL);
	int  GetOrderColum() ;
	int  InsertIndex(int nAt=-1) ;
	int  GetColumCount() ;
	CMyHeaderCtrl *GetHeader() ;

	void ForceRedraw() ;
	BOOL GetCheckCol(int nCol) ;
	void ClearItemSetting() ;

	void SetCheckBoxImg(BOOL bEnable,LPCTSTR lpszImgCheked=NULL,LPCTSTR lpszImgUncheked=NULL) ;

public:
	__int64 GetItemInt(int nItem,int nSubItem);
	void    SetItemInt(int nItem,int nSubItem,__int64 nValue);
	float   GetItemFloat(int nItem,int nSubItem);
	void    SetItemFloat(int nItem,int nSubItem,float fValue,DWORD dwFixed=6);
	double  GetItemDouble(int nItem,int nSubItem);
	void    SetItemDouble(int nItem,int nSubItem,double dbValue,DWORD dwFixed=15);
	int     FindItemText(LPCTSTR lpszText,DWORD dwFindMask=0,int nFromItem=0,int nCol=-1) ;

private:

	void NotifyParent(WPARAM wParam) ;

	DWORD    m_dwCNwParam ;
	DWORD    m_dwDNwParam ;
	DWORD    m_dwTNwParam ;
	DWORD    m_dwHNwParam ;
	int      m_nOrderCol ;
	CString  m_strOrderPre ;
	CString  m_strOrderSub ;
	BOOL     m_bFoucsCell;
	BOOL     m_bHasImage ;
	BOOL     m_bAutoFillLastCol ;
	BOOL     m_bTxtElliPsis  ;
	int      m_nFillInterVal ;
	BOOL     m_bTransParent;
	CString  m_strBkImgFile  ;
	COLORREF m_clrText;
	COLORREF m_clrBk1 ;
	COLORREF m_clrBk2 ;
	COLORREF m_clrActBK;
	COLORREF m_clrActTxt;
	COLORREF m_clrMKBK1;
	COLORREF m_clrMKBK2;
	COLORREF m_clrMKTxt;

	COLORREF m_clrPerBK ;
	COLORREF m_clrPerPrg;
	COLORREF m_clrPerTxt;
	COLORREF m_clrGrid ;
	COLORREF m_nGridWid ;

	BOOL     m_bDrawFoucs ;
	BOOL     m_bCreateEdit;
	BOOL     m_bCreateCmb;
	BOOL     m_bEditShowFullSel;
	BOOL     m_bEnableHeaderAdj;
	
	int      m_nEditedItem;
	int      m_nEditedSubItem;
	int      m_nClickedItem ;
	int      m_nClickedSubItem ;
	int      m_nHitItem    ;
	int      m_nHitSubItem ;
	int      m_nMarkedItem ;
	BOOL     m_bEnableTrack;
	BOOL     m_bReadOnly;

	COLORREF m_clrERowBk ;
	COLORREF m_clrERowTxt;
	COLORREF m_clrDisableBk ;
	COLORREF m_clrDisableTxt;
	BOOL     m_bEnableEvenRowColor;

	int      m_nPercentCols[20];
	int      m_nCheckBoxCols[20];
	int      m_nShowTypeCols[20];
	CPtrList m_ItemBkColor;   //保存Item背景颜色表
	CPtrList m_ItemTextColor; //保存单元格字体颜色
	CPtrList m_ItemIco;       //保存单元格图标
	CPtrList m_ItemImg;       //保存单元格图片
	CPtrList m_ItemCheck;     //保存单元格Check
	CPtrList m_ItemROnly;     //保存单元格ReadOnly
	CPtrList m_ItemDisable;   //保存单元格Disable
	void *GetItemIco(int nRow,int nCol,BOOL bGetAbs=FALSE) ;

	CString m_strChkBoxImgY ;
	CString m_strChkBoxImgN ;
	BOOL m_bEnableChkBoxImg ;

	CPoint   m_oldPt ;
	BOOL     m_bShowTip ;
	CToolTipCtrl *m_pToolTip ;
	CMyHeaderCtrl m_Header;
	int m_nRowHeight ;// 行高
	int m_nLastSCPos ;

	CEdit     *m_pEdit ;
	CComboBox *m_pCmb  ;
	BOOL m_bCanHide ;

	virtual void Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void PreSubclassWindow();	
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent); 
	afx_msg void OnLvnItemdeleted(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnIteminserted(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemclicked(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};

#endif
