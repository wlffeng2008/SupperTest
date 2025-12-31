#if !defined(AFX_UXBUTTON_H__96E4A8C8_02D4_44B2_928F_071BD45AD3F4__INCLUDED_)
#define AFX_UXBUTTON_H__96E4A8C8_02D4_44B2_928F_071BD45AD3F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

const   CString&GetCurrentPath();
const   CString&GetSkinsPath() ;
const   CString&GetAppDataPath() ;
void	SetSkinsPath(LPCTSTR lpPathName);
void	AddSkinsPath(LPCTSTR lpPathName, BOOL bToAdd = TRUE);
CString	GetImagePath(LPCTSTR lpImage);
BOOL	CreateMultiLayerDir(LPCTSTR lpFullPath,BOOL bInclFile=TRUE,BOOL bCreateEmptyFile=FALSE,BOOL bOverWrite=TRUE);
void    GradientFillRect(HDC hDC,LPCRECT rcFill,COLORREF clrBegin,COLORREF clrEnd,BOOL bIsVerticalMode=TRUE) ;
void    GradientFillRectEx(CDC *pDC,LPCRECT rcFill,COLORREF *pColors,int nClrCount,BOOL bRevered=FALSE,BOOL bIsVerticalMode=TRUE) ;
void    DrawMultiLineText(CDC *pDC, LPCTSTR lpText, LPRECT lpRc, COLORREF clrText=0xFF000000,DWORD dwHCnter=DT_CENTER);

HGLOBAL ResizePicture(LPCTSTR lpSrcFile,LPCTSTR lpDestFile,int nWidth=0,int nHeight=0,CBitmap *pRetBitmap=NULL,BOOL bRetMem=FALSE);
void    SetWindowLayered(HWND hWnd,BYTE nLayer=192,COLORREF clrInorge=0) ;

HBITMAP  LoadBmpFormFile(LPCTSTR lpFileName) ;
void *LoadMyImage(LPCTSTR lpImgFile) ;
//0.Center 1.stretch 2.fill 3.fill all ;
BOOL ShowMyImage(LPCTSTR lpImgFile, HDC hDC, LPCRECT rcImg=NULL,DWORD dwMode=0);
BOOL ShowMyImage(void *pImage, HDC hDC, LPCRECT rcImg=NULL,DWORD dwMode=0); 
BOOL ShowMyImage(LPCTSTR lpImgFile, CWnd *pWnd, LPCRECT rcImg=NULL,DWORD dwMode=0);
BOOL ShowMyImage(void *pImage, CWnd *pWnd, LPCRECT rcImg=NULL,DWORD dwMode=0);

HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor, COLORREF cTolerance = RGB(0,0,0)); 
void DrawTransparentBitmap(CDC *pDC, CBitmap *pSrcBM, LPRECT lpBmpRc, COLORREF crColour= RGB(255,0,255));
void SetAutoRunOnStart(LPCTSTR lpszName=NULL,BOOL bAddFlag=TRUE,LPCTSTR lpszEXEPath=NULL,LPCTSTR lpszParam=NULL,BOOL bForAllUser=FALSE);
BOOL IsAutoRunFlagExist(LPCTSTR lpszName=NULL,LPCTSTR lpszEXEPath=NULL,BOOL bForAllUser=FALSE);
enum DrawMode{DCenter,DFull,DFill,DScale};

class CImageEx  
{
public:
	CImageEx();
	virtual ~CImageEx();

	int  Start(HWND hWndDisp, DWORD dwImageID);
	int  Start(HWND hWndDisp, LPCTSTR lpImageFile);
	void Stop(BOOL bDestroy=TRUE);
	void Pause();
	long GetSpeed();
	void EnableClickToPause(BOOL bEnable=TRUE);
	void OnDraw();
	void SetDrawPicFrame(BOOL bDraw=TRUE,COLORREF clrFrm=RGB(210,210,210));
	void SetDrawMode(DrawMode wMode) ;
	void SetGifBkColor(COLORREF clrBk);

	DWORD  m_dwOldProc;
	HWND   m_hWndDisp ;
	double m_dbImgScale;
	BOOL   m_bClickToPause;
	int	   m_nImagW ;
	int	   m_nImagH ;

protected:
	void SetNewProc();
	void RestoreOldProc();
	long GetFrameCur();
	void AddFrameCur();
	int  PlayAnimate();
	static UINT ThreadPlayGif(LPVOID pParam);

	DWORD    m_nFrameCount;
	COLORREF m_clrGifBk;
	COLORREF m_clrFrame ;
	WORD     m_wDrawMode;
	DWORD	 m_nFrameCur ;
	HANDLE	 m_hExitEvent;
	void	*m_pImage ;
	long	*m_parrSpeed;
	BOOL	 m_bToDestroy;
	BOOL	 m_bDrawFrame;
	BOOL	 m_bPause;
};

void DoUpdateToolTip() ;


class CUxButton : public CButton
{
public:
	CUxButton();
	virtual ~CUxButton();
	
	void Draw();
	void SetTransparentMode(BOOL bTrans=TRUE) ;
	void SetBitmapID(int nNorID,int nDownID=-1,int nDisableID=-1) ;
	void SetBitmapPath(LPCTSTR lpNorPath,LPCTSTR lpHoverPath=NULL,LPCTSTR lpHoldPath=NULL,LPCTSTR lpDisablePath=NULL) ;
	void SetHold(BOOL bHold = TRUE);
	BOOL GetHold();
	void SetHoldText(LPCTSTR lpszHoldTxt) ;
	void SetClickHold(BOOL bSet=TRUE) ;
	void SetHitOver(BOOL bHitOver=TRUE);
	void SetDrawPicFrame(BOOL bDrawFlag=TRUE);
	void SetDrawTextFlag(BOOL bDrawFlag=TRUE);
	void SetToolTipTxt(LPCTSTR lpTipTxt=NULL);
	void GetRoundXY(int &nX,int &nY) ;
	void SetBtnImageList(CImageList *pImageList=NULL,int nImageIndex=-1) ;
	void SetNoFocusRect(BOOL bNoFocusRect=TRUE);
	void SetInProtect(BOOL bInProtect=TRUE);
	void EnableToolTip(BOOL bEnable=TRUE);
	void SetIconImage(LPCTSTR lpszNorIcoFile=NULL,LPCTSTR lpszOvrIcoFile=NULL,LPCTSTR lpszHldIcoFile=NULL) ;
	
	static void SetAllGrendClr(COLORREF clrB,COLORREF clrE);
	void SetGrendClr(COLORREF clrB,COLORREF clrE,BOOL bRetToDef=FALSE);

	static void SetAllFrameClr(COLORREF clrFrm);
	void SetFrameClr(COLORREF clrFrm,BOOL bRetToDef=FALSE);

	static void SetAllTextClr(COLORREF clrFrm);
	void SetTextClr(COLORREF clrFrm,BOOL bRetToDef=FALSE);

	static void SetAllTextOverClr(COLORREF clrFrm);
	void SetTextOverClr(COLORREF clrFrm,BOOL bRetToDef=FALSE);

	static void SetAllRoundScale(int nX,int nY);
	void SetRoundScale(int nX,int nY,BOOL bRetToDef=FALSE);

	static void SetAllImgOffset(int nX,int nY);
	void SetImgOffset(int nX,int nY,BOOL bRetToDef=FALSE);

	static void SetAllHoldColor(COLORREF clrHoldBk1=-1,COLORREF clrHoldBk2=-1,COLORREF clrHoldTxt=-1,COLORREF clrHoldFrm=-1);
	void SetHoldColor(COLORREF clrHoldBk1=-1, COLORREF clrHoldBk2=-1,COLORREF clrHoldTxt=-1,COLORREF clrHoldFrm=-1, BOOL bSetToDef = FALSE);

	static void SetAllOverBKClr(COLORREF clrOverBk1=-1, COLORREF clrOverBk2=-1, COLORREF clrOverTxt=-1,COLORREF clrOverFrm=-1);
	void SetOverBKClr(COLORREF clrOverBk1=-1, COLORREF clrOverBk=-1,COLORREF clrOverTxt=-1,COLORREF clrOverFrm=-1, BOOL bSetToDef = FALSE);

	static void SetAllFontStyle(int nFontSize=-1,BOOL bULine=FALSE,BOOL bItaic=FALSE,BOOL bBold=FALSE) ;
	void SetFontStyle(int nFontSize=-1,BOOL bULine=FALSE,BOOL bItaic=FALSE,BOOL bBold=FALSE, BOOL bSetToDef = FALSE) ;

	static void LoadButtonDefault();
	
	CString  m_strNorBmpPath ;
	CString  m_strHoverBmpPath;	
	CString  m_strDisbaleBmpPath;
	CString  m_strHoldBmpPath;

private:
	CToolTipCtrl *m_pToolTip ;
	CImageList   *m_pBtnImgList;
	int		 m_nRX ;
	int		 m_nRY ;
	int		 m_nImgIndex;
	int		 m_nImgOffsetX;
	int		 m_nImgOffsetY;
	CString  m_strNorIcoImg ;
	CString  m_strHldIcoImg ;
	CString  m_strOvrIcoImg ;

	COLORREF m_clrText   ;
	COLORREF m_clrGrendB ;
	COLORREF m_clrGrendE ;
	COLORREF m_clrFrame  ;

	COLORREF m_clrOverBk1;
	COLORREF m_clrOverBk2;
	COLORREF m_clrOverTxt;
	COLORREF m_clrOverFrame ;

	COLORREF m_clrHoldBk1 ;
	COLORREF m_clrHoldBk2 ;
	COLORREF m_clrHoldTxt ;
	COLORREF m_clrHoldFrame ;

	CString m_strHoldTxt ;

	DWORD	 m_dwNorBitID  ;
	DWORD	 m_dwDownBitID ;
	DWORD	 m_dwDisableBitID ;
	TCHAR    m_strTipText[256] ;

	int      m_nFontSize ;
	BOOL     m_bShowULine;
	BOOL     m_bShowItaic;
	BOOL     m_bShowBold;
	TCHAR 	 m_szFontName[128] ;

	BOOL	 m_bHold ;
	BOOL	 m_bHitOver ;
	BOOL	 m_bOvering ;
	BOOL	 m_bIsBitMapBtn ;
	BOOL	 m_bMouseDown ;
	BOOL	 m_bDrawSelfText ;
	BOOL     m_bTransMode ;
	BOOL     m_bNoFocusRect;
	BOOL     m_bInProtect;
	BOOL     m_bEnableTT ;
	BOOL     m_bClkHold ;
	void *BuildBtnFont(int nType=0) ;


	//{{AFX_VIRTUAL(CUxButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CUxButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CMyCheckButton:public CButton
{
public:
	CMyCheckButton();
	virtual ~CMyCheckButton();

	void SetToolTipTxt(LPCTSTR lpTipTxt=NULL);
	void EnableToolTip(BOOL bEnable=TRUE);

	void SetImagePos(int nImgPosX,int nImgPosY) ;
	void SetImageSize(int nWidth,int nHeight) ;
	void SetImageToRight(BOOL bSetToRight=TRUE,BOOL bHideText=FALSE) ;
	void SetNormalImage(LPCTSTR lpszCheckedImg=NULL,LPCTSTR lpszUncheckImg=NULL,BOOL bHideTxt=FALSE) ;
	void SetHoverImage(LPCTSTR lpszCheckedHoverImg=NULL,LPCTSTR lpszUncheckHoverImg=NULL,BOOL bHideTxt=FALSE) ;
	void SetTextColor(DWORD dwColor,int nType=0) ;
	void SetBackColor(DWORD dwColor,int nType=0) ;

	static void SetDefaultChkSize(int nWitdth=20,int nHeight=20) ;
	static void SetDefaultImage(LPCTSTR lpszCheckedImg,LPCTSTR lpszUncheckImg,int nType=0) ;
	static void SetDefaultColor(DWORD dwClrText=-1,DWORD dwClrBk=-1,int nType=0) ;

private:
	void Draw();

	CToolTipCtrl *m_pToolTip ;

	BOOL    m_bIsRadioStyle ;
	BOOL	m_bOvering ;

	BOOL	m_bMouseDown ;
	BOOL    m_bEnableTT ;
	TCHAR   m_strTipText[256] ;
	DWORD   m_dwChecked ;
	BOOL    m_bImgAtRight ;
	BOOL    m_bHideText ;

	CString m_strCheckedImg ;
	CString m_strUncheckImg ;
	CString m_strCheckedHoverImg ;
	CString m_strUncheckHoverImg ;

	COLORREF m_clrTxtHover   ;
	COLORREF m_clrTxtChecked ;
	COLORREF m_clrTxtUncheck ;

	COLORREF m_clrBKHover   ;
	COLORREF m_clrBKChecked ;
	COLORREF m_clrBKUncheck ;
	
	int m_nImgPosX ;
	int m_nImgPosY ;
	int m_nImgWidth ;
	int m_nImgHeight ;
	
	//{{AFX_VIRTUAL(CMyCheckButton)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CMyCheckButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




#endif 
