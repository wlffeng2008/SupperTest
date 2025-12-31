# if !defined(AFX_LABEL_H__59128F70_6CC6_11D4_BD73_000021479D21__INCLUDED_)
#define AFX_LABEL_H__59128F70_6CC6_11D4_BD73_000021479D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#define NM_LINKCLICK       (WM_APP  + 0x200)
#define WM_CLICKSTATICCTRL (WM_USER + 0x300)

class CLabel : public CStatic
{
public:
	CLabel();
	virtual ~CLabel();
	void SetFlashTime(DWORD dwTime = 0);
	void SetFlashColor(COLORREF crText, COLORREF crBkgnd = RGB(0, 0, 0));
	void SetBkColor(COLORREF crBkgnd);
	DWORD GetBkColor();
	void SetColorPickup(BOOL bSet=TRUE) ;
	void SetTextColor(COLORREF crText);
	void SetHoverColor(COLORREF crHoverText);
	void SetLabelText(LPCTSTR lpLabelTxt = NULL,BOOL bForHold=FALSE);
	void SetFontBold(BOOL bBold = TRUE);
	void SetFontName(LPCTSTR lpFontName = NULL);
	void SetFontUnderline(BOOL bSet = TRUE);
	void SetFontItalic(BOOL bSet = TRUE);
	void SetFontSize(int nSize);
	void SetImageList(CImageList *pImgList,int nIndex=0);

	void SetLink(BOOL bLink, BOOL bNotifyParent);
	void SetRotationAngle(UINT nAngle, BOOL bRotation = TRUE);

	void SetParentBkMemDC(CDC *pPBkMemDC, int nX, int nY, int nWidth, int nHeight);
	void SetBkBitmap(DWORD dwbtID,BOOL bHideTxt=TRUE);
	void SetBkBitmap(CBitmap *pBkbitmap = NULL,BOOL bHideTxt=TRUE);
	void SetBkBitmap(LPCTSTR lpszName,BOOL bHideTxt=TRUE);
	void SetBkBitmapEx(LPCTSTR lpszName1,LPCTSTR lpszName2,BOOL bHideTxt=TRUE);
	void SetIconImage(LPCTSTR lpszName,int nIcoW=-1,int nIcoH=-1,int nPosX=-1,int nPosY=-1);
	void SetIconPos(int nAlign=0,int nMargin=5);
	void SetAlign(DWORD dwAlign = 0);
	void SetTransparent(BOOL bTrans = TRUE);
	void SetHold(BOOL bHold=TRUE) ;
	BOOL GetHold() ;
	void SetHoldColor(COLORREF clrSet,BOOL bForTxt=TRUE) ;
	void SetClickHold(BOOL bSet=TRUE) ;

	void SetAsTimeItem(BOOL bToSet=TRUE,DWORD dwTimeFM=0,LPCTSTR lpszTimePre=NULL) ;
	void SetShowBkRGB(BOOL bShow=TRUE,BOOL bHexFmt=TRUE) ;

	void SetCheckChar(LPCTSTR lpszCheckedChar=NULL,LPCTSTR lpszUncheckChar=NULL) ;
	void SetCheckImg(LPCTSTR lpszCheckedImg  =NULL,LPCTSTR lpszUncheckImg=NULL,BOOL bHideTxt=TRUE) ;
	void SetCheckHoverImg(LPCTSTR lpszCheckedHoverImg  =NULL,LPCTSTR lpszUncheckHoverImg=NULL,BOOL bHideTxt=TRUE) ;
	void SetCheckColor(DWORD clrChecked=NULL,DWORD clrUncheck=NULL) ;
	void SetCheckMode(DWORD dwCheckMode=1,BOOL bReadOnly=TRUE,LPCTSTR lpszCheckedImg=NULL,LPCTSTR lpszUncheckImg=NULL) ;
	void SetCheck(BOOL bSetCheck=TRUE) ;
	BOOL GetCheck() ;

	static void SetDefaultChkSize(int nWitdth=100,int nHeight=25) ;
	static void SetDefaultChkImg(LPCTSTR lpszCheckedImg,LPCTSTR lpszUncheckImg) ;
	static void SetDefaultChkHoverImg(LPCTSTR lpszCheckedHoverImg,LPCTSTR lpszUncheckHoverImg) ;

protected:
	void DrawLabel(CDC *pRDC);
	void ReconstructFont();
	COLORREF    m_crBkGround;
	COLORREF    m_crFlashBkGround;
	COLORREF    m_crText;
	COLORREF    m_crHoverText;
	COLORREF    m_crFlashText;
	LOGFONT     m_lf;
	CFont       m_font;
	BOOL        m_bHideTxt ;
	CString     m_strText;
	CString     m_strHoldTxt ;
	BOOL        m_bState;
	BOOL        m_bLink;
	BOOL        m_bUnderLine;
	BOOL        m_bBeclicked ;
	BOOL        m_bTransparent;
	BOOL        m_bNotifyParent;
	BOOL        m_bRotation;
	DWORD       m_dwAlign;
	BOOL        m_bitmapBk;
	DWORD       m_bitmapID;
	CDC         *m_pParentBKMemDC;
	CBitmap     *m_pBkbitmap;
	CString     m_strBkImg1;
	CString     m_strBkImg2;
	CString     m_strIconImg;
	int         m_nIcoMargin;
	int         m_nIcoPosX;
	int         m_nIcoPosY;
	int         m_nIcoW;
	int         m_nIcoH;
	int         m_nIcoAlign;
	int         m_nParXPos;
	int         m_nParYPos;
	int         m_nParWidth;
	int         m_nParHeight;
	BOOL        m_bSetHand;
	BOOL        m_bMouseIn;

	DWORD       m_dwTimeFM ;
	BOOL        m_bTimeItem;
	BOOL        m_bHold  ;
	BOOL        m_bClkSetHold ;
	COLORREF    m_clrHoldBK ;
	COLORREF    m_clrHoldTxt ;

	BOOL        m_bShowBkRGB ;
	BOOL        m_bShowBkHex ;
	BOOL        m_bClrPickup ;

	int          m_nImgIndex ;
	CImageList  *m_pImgList ;

	DWORD    m_dwCheckMode;
	BOOL     m_bChecked  ;
	BOOL     m_bCheckROnly  ;
	COLORREF m_clrChecked ;
	COLORREF m_clrUncheck ;
	CString  m_strCheckedImg ;
	CString  m_strUncheckImg ;
	CString  m_strCheckedHoverImg ;
	CString  m_strUncheckHoverImg ;

	CString  m_strCheckedChar ;
	CString  m_strUncheckChar ;
	CString  m_strTimePre ;

	//{{AFX_VIRTUAL(CLabel)
public:
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CLabel)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif