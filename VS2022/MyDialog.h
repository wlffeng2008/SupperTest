#pragma once


#include <AFXTEMPL.H>
#include <ATLCONV.H>
#include <gdiplus.h>
using namespace Gdiplus;
#include <winsock.h>

#include "Label.h"
#include "UxButton.h"
#include "IniAX.h"

#define SYSTEM_BUTTON_ID     0x4900
#define IDC_BUTTON_CLSDLG	 (SYSTEM_BUTTON_ID - 0)
#define IDC_BUTTON_MAXDLG    (SYSTEM_BUTTON_ID - 1)
#define IDC_BUTTON_MINDLG    (SYSTEM_BUTTON_ID - 2)
#define IDC_BUTTON_TOPDLG    (SYSTEM_BUTTON_ID - 3)
#define IDC_BUTTON_SETDLG    (SYSTEM_BUTTON_ID - 4)
#define IDC_BUTTON_SNAPDLG   (SYSTEM_BUTTON_ID - 5)

#define CMD_CUSTUM_MAX		 0x5000
#define CMD_CUSTUM_MIN		 (CMD_CUSTUM_MAX -512)

#define CMD_COMLIST_MIN		 (CMD_CUSTUM_MAX -256)
#define CMD_COMLIST_MAX		 (CMD_CUSTUM_MAX -128)

#define CMD_MOUSECLICKITEM   (CMD_CUSTUM_MAX - 0) // OnCommand(pParam)
#define CMD_SCROLLER_CHANGE  (CMD_CUSTUM_MAX - 1)
#define CMD_LBUTTON_PRESS    (CMD_CUSTUM_MAX - 2)
#define CMD_LBUTTON_RELEASE  (CMD_CUSTUM_MAX - 3)
#define CMD_LBUTTON_DBCLICK  (CMD_CUSTUM_MAX - 4)
#define CMD_RBUTTON_PRESS    (CMD_CUSTUM_MAX - 5)
#define CMD_RBUTTON_RELEASE  (CMD_CUSTUM_MAX - 6)
#define CMD_RBUTTON_DBCLICK  (CMD_CUSTUM_MAX - 7)
#define CMD_MOUSEENTER       (CMD_CUSTUM_MAX - 8)
#define CMD_MOUSELEAVE       (CMD_CUSTUM_MAX - 9)
#define CMD_MOUSEWHEEL       (CMD_CUSTUM_MAX -10)
#define CMD_USBDEVICE_NOTIFY (CMD_CUSTUM_MAX -11)
#define CMD_TRAYICON_NOTIFY  (CMD_CUSTUM_MAX -12)
#define CMD_DROPFILES_NOTIFY (CMD_CUSTUM_MAX -13)
#define CMD_LISTCTRL_COLCLK  (CMD_CUSTUM_MAX -14)
#define CMD_LISTCTRL_COLDCK  (CMD_CUSTUM_MAX -15)
#define CMD_LISTCTRL_COLTXT  (CMD_CUSTUM_MAX -16)
#define CMD_LISTCTRL_COLHIT  (CMD_CUSTUM_MAX -17)

#define CMD_COMSEL_NOTIFY    (CMD_CUSTUM_MAX -20)

typedef enum
{
	CTRL_TYPE_BUTTON,
	CTRL_TYPE_STATIC,
	CTRL_TYPE_EDIT,
	CTRL_TYPE_COMBOBOX,
	CTRL_TYPE_LISTBOX,
	CTRL_TYPE_LISTCTRL,

}DlgCtrlType;

void ShowPopupMenu(CMenu *pMenu,CWnd *pParent,int nXPos=-1,int nYPos=-1,DWORD dwPos=2) ;
void ShowPopupMenuOnDlgItem(CMenu *pMenu,UINT nItemID,CWnd *pParent,DWORD dwPos=2) ;
void ShowPopupMenuOnDlgItem(CMenu *pMenu,CWnd *pItemID,CWnd *pParent,DWORD dwPos=2) ;
int  BreakStringToArray(LPCTSTR lpszSrc,CStringArray&arrOut,LPCTSTR lpszDiv=_T(","));
CString BuildStringFromArray(CString&strOut,CStringArray&arrIn,LPCTSTR lpszDiv=_T(","));
void SetWindowsTaskBar(BOOL bAutoHide=TRUE) ;
void PickFiles(LPCTSTR lpszPath,CStringArray&arrFiles,LPCTSTR lpszType=_T("*.*"),BOOL bGetSubDir=FALSE) ;
void DeletePath(LPCTSTR lpszPath) ;
DWORD QGetRegValue(LPCTSTR lpszPath,LPCTSTR lpszItem,VOID *pszGetBuf,DWORD dwValType=REG_SZ,HKEY hRoot=HKEY_LOCAL_MACHINE);
DWORD QSetRegValue(LPCTSTR lpszPath,LPCTSTR lpszItem,VOID *pszSetBuf,DWORD dwBufLen,DWORD dwValType=REG_SZ,HKEY hRoot=HKEY_LOCAL_MACHINE);

CFileStatus *GetFileST(LPCTSTR lpszFileName);
BOOL IsAFolder(LPCTSTR lpszFileName);
LPCTSTR GetGUID(TCHAR *pszRet=NULL);
BOOL RegisterOCX(LPCTSTR lpszDllName);
void RedrawWnd(CWnd *pWnd) ;
BOOL IsActiveWindow(CWnd* pWnd);
BOOL IsCursorInWindow(CWnd* pWnd);
BOOL IsCursorInRect(LPRECT lpRect);
void ShowMyCursor(BOOL bShow);
int  GetMyInstanceIndex() ;

//0:JPG 1:PNG 2:BMP 3:GIF 4:TIFF
BOOL SaveBitmap(Image *pImg,LPCTSTR lpszFileName,int nType=1,int nQuality=100);
BOOL SaveBitmap(HBITMAP hMemBM,LPCTSTR lpszFileName,int nType=1,int nQuality=100);
BOOL GetWindowSnap(HWND hWnd,LPCTSTR lpszFileName,int nX1=0,int nY1=0,int nX2=0,int nY2=0,int nType=1,int nQuality=100);

class  CMyComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CMyComboBox)
public:
	CMyComboBox();
	virtual ~CMyComboBox();

	void SetItemText(int nItem, LPCTSTR lpszText);
	LPCTSTR GetItemText(int nItem);
	
	static void SetCmbThumbDefBtIDs(int dwNormal, int dwHover, int dwDown) ;
	void SetCmbThumbBtIDs(int dwNormal, int dwHover, int dwDown) ;
	static void SetCmbThumbDefBmpPaths(LPCTSTR lpNormal, LPCTSTR lpHover, LPCTSTR lpDown) ;
	void SetCmbThumbBmpPaths(LPCTSTR lpNormal, LPCTSTR lpHover, LPCTSTR lpDown) ;

private:
	BOOL	m_bMouseIn  ;
	int     m_dwNormalBtID;
	int     m_dwHoverBtID ;
	int     m_dwDownBtID  ;
	CString m_strNormalPic ;
	CString m_strHoverPic  ;
	CString m_strDownPic   ;
	
	//{{AFX_VIRTUAL(CMyComboBox)
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CMyComboBox)
	afx_msg void OnPaint();
	afx_msg void OnCloseup();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg void OnKillfocus();
	afx_msg void OnSetFocus();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

class CMyEdit : public CEdit
{
public:
	CMyEdit();
	virtual ~CMyEdit();

	void SetTipText(LPCTSTR lpszTip=NULL) ;
	void SetEditColor(COLORREF clrEdit,int nType=0,BOOL bSetDef=FALSE) ;// 0 Text 1 Bk  2 Tip
	static void SetEditDefaultColor(COLORREF clrText,COLORREF clrBK,COLORREF clrTip) ;
public:
	CString  m_strTip ;
	COLORREF m_clrTip ;
	COLORREF m_clrBK  ;
	COLORREF m_clrTxt ;
	BOOL m_bTransparent ;

	//{{AFX_VIRTUAL(CMyEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMyEdit)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#define  GEN_REDRAW_BUTTON   0x00000001
#define  GEN_REDRAW_COMBOX   0x00000002
#define  GEN_REDRAW_LISTCTRL 0x00000004
#define  GEN_REDRAW_LISTBOX  0x00000008
#define  GEN_REDRAW_PROGCTRL 0x00000010
#define  GEN_REDRAW_MYLABEL  0x00000020
#define  GEN_REDRAW_SLIDCTRL 0x00000040
#define  GEN_REDRAW_CHKCTRL  0x00000080

void  SetMyGUILang(DWORD dwLangID) ;
DWORD GetMyGUILang() ;
void  PutMyGUILang(DWORD dwLangID) ;

typedef struct
{
	DWORD  dwItemType ;
	CWnd  *pGrpBoxWnd ;
	CBrush GrpBoxBR   ;
}GroupBrush;

typedef struct
{
	DWORD  dwItemID ;
	DWORD  dwType ;
	double dbStep ;
}WheelValue;

typedef struct
{
	DWORD  dwItemID ;
	COLORREF clrTxt ;
	COLORREF clrBk  ;
	CBrush   Brush;
}GroupColor;

typedef struct
{
	int nPosX;
	int nPosY;
	int nW;
	int nH;
	int nBorderThickness;
	BOOL bFillH  ;
	int nColorCnt ;
	COLORREF clrBorder ;
	COLORREF clrGrdFills[20] ;
}MyFillRect;

typedef struct
{
	int nX1;
	int nY1;
	int nX2;
	int nY2;
	int nLineThickness;
	DWORD dwLineStyle ;
	COLORREF clrLine ;
}MyDrawLine;

typedef struct
{
	int nPosX;
	int nPosY;

	int nFontSize;
	float fAngle ;
	TCHAR szText[1024] ;
	TCHAR szFontName[64] ;

	COLORREF clrTxt ;
	COLORREF clrBK ;
	CFont *pTFont ;
}MyDrawText;

typedef struct
{
	int nPosX;
	int nPosY;
	int nWidth;
	int nHeight;

	float fAngle ;
	TCHAR szImgPath[MAX_PATH] ;

	COLORREF clrBK ;
}MyDrawImage;

typedef struct
{
	DWORD  dwEditID ;
	COLORREF clrFoucsFrame;
	COLORREF clrHoverFrame;
	COLORREF clrFoucsBack;
	COLORREF clrHoverBack;
	COLORREF clrFoucsText;
	COLORREF clrHoverText;
}MyEditColor;

typedef struct
{
	CWnd *pWnd ;
	int  nLeft;
	int  nRight;
	int  nTop;
	int  nBottom;
}MyMargin;

typedef struct  
{
	UINT  nClickID ;
	UINT  nPathID ;
	BOOL  bIsOpen ;
	BOOL  bIsFolder ;
	TCHAR szFilter[300] ;
}QFileOPBind;

typedef struct
{
	TCHAR szName[128] ;
	UINT nIDs[6];
	UINT nSels[6];

}EasyCOMSetting;

typedef struct
{
	UINT nSliderID;
	UINT nBindID ;
	FLOAT fFactor ;
}SliderBindItem;

//WM_MBUTTONUP + VK_MENU + VK_CONTROL //Load Dialog Lang
//WM_MBUTTONUP + VK_MENU + VK_SHIFT   //Export Dialog Lang
//WM_LBUTTONUP + VK_CONTROL + 'A'     //Copy All item's text of the dialog
//WM_LBUTTONDOWN + VK_CONTROL + 'C'   //Copy the clicked Item's Text 

//Copy all Item's text of a CListCtrl,CListBox, CComboBox
//WM_KEYUP + VK_CONTROL + 'A' (All items)  'C' or 'S' (Selected items)  'L' ( A column's text)

typedef enum
{
	TIMER_SETDLGFONT=2201,
	TIMER_SETCAPBTNPOS=2202,
	TIMER_SETBUTTONTIP=2203,
	TIMER_MAKEGRPBOXBRUSH=2204,
	TIMER_MAKELANGTEMPL=2205, //Alt+Left+L
	TIMER_CPYDLGTEXT_EX=2206, //Ctrl+Right
	TIMER_IMPORTLANG=2207,
	TIMER_EXPORTLANG=2208,
	TIMER_REDRAWITEMS=2209,
	TIMER_CHECKLANG=2210,
	TIMER_UPDATEEDIT=2211,
	TIMER_SETLANGUAGE=2212,
	TIMER_INNERMAX=2220

}INNERTIMER;

#define MAX_SIMPLETHREAD_COUNT 64 

class CMySimpleThread
{
public:
	CMySimpleThread();
	virtual ~CMySimpleThread();
	
	BOOL GetWorkingFlag(int nWorkerID) ;
	virtual int OnSimpleThreadLoopRun(int nWorkerID) ;

	void StartMultiThread(int nCount,int nBegin=0);
	void StopMultiThread(int nCount,int nBegin=0);
	void StartThread(int nWorkerID);
	void StopThread(int nWorkerID);

	void SimpleLock(int nCSIndex) ;
	void SimpleUnlock(int nCSIndex) ;

	DWORD SimpleWait(int nEventIndex,DWORD dwWait=INFINITE) ;
	DWORD SimpleFire(int nEventIndex) ;
	
	BOOL  m_bEndAllThread ;
	VOID ForceEnd() ;

private:
	BOOL   m_bWorkings[MAX_SIMPLETHREAD_COUNT] ;
	HANDLE m_hEvents[MAX_SIMPLETHREAD_COUNT] ;
	HANDLE m_hThreadHandles[MAX_SIMPLETHREAD_COUNT] ;
	CRITICAL_SECTION *m_CSs[MAX_SIMPLETHREAD_COUNT] ;

	static DWORD WINAPI ThreadWorker(LPVOID lpParam) ;
	BOOL StartSimpleThreadByID(int nWorkerID,BOOL bToStart=TRUE) ;
};

class CEasyComPort ;
class CMyListCtrl ;
class CMyListBox ;
class CMyProgressCtrl ;
class CMySliderCtrl ;

class CMyDialog : public CDialog, public CMySimpleThread
{
	DECLARE_DYNAMIC(CMyDialog)
public:
	CMyDialog(UINT uDlgID,CWnd* pParent = NULL);
	virtual~CMyDialog() ;

	void SetDialogID(UINT nDlgID) ;
	void SetDlgFont(CFont *pFont) ;
	void SetDlgFontSize(float fFontSize) ;
	void DoForceRedraw() ;
	void SetDlgSize(int nW,int nH,BOOL bAdjItem=TRUE,BOOL bSetCenter=TRUE) ;
	DWORD GetDlgSize(int&nW,int&nH) ;
	void SetDlgPos(int nX,int nY,BOOL bRedraw=TRUE) ;
	void SetDlgItemFixedFont(UINT nID,BOOL bToSet=TRUE) ;
	void SetDlgItemFont(UINT nID, CFont* pFont);
	void SetDlgItemFont(CWnd* pItem, CFont* pFont);
	void SetDlgItemFont(UINT nID,int nFontSize,int nBold=400,LPCTSTR lpszFontName=NULL) ;
	void SetDlgItemFont(CWnd *pItem,int nFontSize,int nBold=400,LPCTSTR lpszFontName=NULL) ;
	void SetDlgItemColor(CWnd *pItem,COLORREF clrTxt = 0,COLORREF clrBK = 0xFFFFFFFF);
	void SetDlgItemColor(UINT nID,COLORREF clrTxt = 0,COLORREF clrBK = 0xFFFFFFFF);

	void SetDlgGUILang(DWORD dwLangID=0) ;
	DWORD GetDlgGUILang() ;
	void PutDlgGUILang(DWORD dwLangID) ;
	virtual void OnLanguageChanged(DWORD dwLangID) ;
	TCHAR *GetLangText(int nTxtID) ;
	void SetLangText(int nTxtID,LPCTSTR lpszTxt);
	void ClipWindowEge(int nLen,DWORD dwFlag=1) ;
	void SendCmdToParent(UINT nCmd,int nValue=0) ;

	void AttachDlgItem(CWnd* pWnd, CWnd* pToWnd, int nPos = 1, int nDist = 0);
	void ExtendDlgItem(UINT nID,int nLen,DWORD dwFlag) ;//flag0 top 1bottom 2left 3right
	void ExtendDlgItem(CWnd *pWnd,int nLen,DWORD dwFlag) ;
	void SetEditReadOnly(UINT nID, BOOL bSetReadOnly=TRUE);
	void SetEditPasswordVisable(UINT nID, BOOL bVisable=TRUE);
	void SetDlgItemMargin(UINT nID,int nTop = -1,int nBottom = -1,int nLeft = -1,int nRight = -1) ;
	void SetDlgItemMargin(CWnd *pWnd,int nTop = -1,int nBottom = -1,int nLeft = -1,int nRight = -1) ;
	void SetDlgItemAlign(UINT nID,int nOffset,int nDir) ;
	void SetDlgItemAlign(CWnd *pItemWnd,int nOffset,int nDir) ;
	void SetDlgItemPos(CWnd *pWnd,int nX,int nY,BOOL bAbs=TRUE);
	void SetDlgItemPos(UINT nID,int nX,int nY,BOOL bAbs=TRUE);
	void SetDlgItemCenter(UINT nID,int nX,int nY) ;
	void SetDlgItemCenter(CWnd *pWnd,int nX,int nY) ;
	void SetDlgItemSize(CWnd *pWnd,int nW,int nH);
	void SetDlgItemSize(UINT nID,int nW,int nH);
	DWORD GetDlgItemSize(CWnd *pWnd,int&nW,int&nH);
	DWORD GetDlgItemSize(UINT nID,int&nW,int&nH);
	DWORD GetDlgItemWidth(CWnd *pWnd);
	DWORD GetDlgItemWidth(UINT nI);
	DWORD GetDlgItemHeight(CWnd *pWnd);
	DWORD GetDlgItemHeight(UINT nID);
	DWORD GetDlgWidth();
	DWORD GetDlgHeight();
	void  SetDlgItemFitImage(UINT nBtnID,LPCTSTR lpszImage) ;

	BOOL GetDlgItemPos(UINT nID,LPRECT lprc);
	BOOL GetDlgItemPos(CWnd *pWnd,LPRECT lprc);
	BOOL GetDlgItemRect(UINT nID,LPRECT lprc) ;
	HWND GetDlgItemWnd(UINT nID) ;
	BOOL SetDlgItemPos2(UINT nID,UINT nID2,BOOL bHide2=TRUE) ;
	BOOL SetDlgItemPos2(CWnd *pWnd,UINT nID2,BOOL bHide2=TRUE) ;

	void SetDlgItemMBChar(UINT nID, CHAR* pMCharText);
	void GetDlgItemMBChar(UINT nID, CHAR* pMCharText,int nMaxLen=128);
	void SetButtonBmp(UINT nBtnID, LPCTSTR lpBmp1, LPCTSTR lpBmp2 = NULL, LPCTSTR lpBmp3 = NULL, BOOL bFitImg = FALSE);
	void SetButtonTip(UINT nBtnID, LPCTSTR lpTips);
	void SetButtonText(UINT nBtnID, LPCTSTR lpText, BOOL bUpdateTip = TRUE);
	void SetButtonsColor( COLORREF clrText, COLORREF clrBK1 = 0xFFFFFFFF, COLORREF clrBK2 = 0xFFFFFFFF);
	void SetDlgBKColor(COLORREF clrBK) ;
	void SetDlgFRColor(COLORREF clrFR,BOOL bUseToButton=TRUE) ;
	void SetDlgEditFoucsFrame(UINT nID,COLORREF clrFrame) ;
	void SetDlgEditFoucsFrame(COLORREF clrFrame) ;

	static void SetEnableButtonDefaultImage(BOOL bAllow=TRUE);
	static void SetDlgDefaultColor(COLORREF clrBK,COLORREF clrFR) ;
	static void SetDlgDefaultFrame(COLORREF clrFrame);
	static void SetDlgDefaultGradBKColors(COLORREF *pBKclrs,int nCount);
	static void SetDlgDefaultEditFoucsFrame(COLORREF clrFoucsFrame) ;

	void EnableDlgItem(UINT nID,BOOL bEnable=TRUE);
	void ShowDlgItem(UINT nID,BOOL bShow=TRUE) ;
	void FlatDlgItem(UINT nID,BOOL bDrawFrame=TRUE) ;
	void RedrawDlgItem(UINT nID,BOOL bForce=FALSE) ;
	void RedrawDlgItem(CWnd *pWnd,BOOL bForce=FALSE) ;

	void SetDlgItemEnabled(UINT nID,BOOL bEnable=TRUE) ;
	BOOL GetDlgItemEnabled(UINT nID) ;
	void SetDlgItemVisible(UINT nID,BOOL bVisible=TRUE) ;
	BOOL GetDlgItemVisible(UINT nID) ;

	float  GetDlgItemFloat(UINT nID) ;
	void   SetDlgItemFloat(UINT nID,float fValue,int nDivCount=6,LPCTSTR lpszPrefix=NULL,LPCTSTR lpszSuffix=NULL) ;
	double GetDlgItemDouble(UINT nID) ;
	void   SetDlgItemDouble(UINT nID,double dValue,int nDivCount=14,LPCTSTR lpszPrefix=NULL,LPCTSTR lpszSuffix=NULL) ;
	CString GetDlgItemTextEx(UINT nID) ;
	void    SetDlgItemTextSP(UINT nID,LPCTSTR lpszText) ;
	void    SetDlgItemTextEx(UINT nID,LPCTSTR lpszText,LPCTSTR lpszPrefix=NULL,LPCTSTR lpszSuffix=NULL) ;
	void  SetDlgItemIntEx(UINT nID,int nVal,BOOL bHexShow=FALSE,LPCTSTR lpszPrefix=NULL,LPCTSTR lpszSuffix=NULL);
	int   GetDlgItemIntEx(UINT nID,BOOL bHexShow=FALSE);
	void  SetDlgItemIntRange(UINT nID, int nVal, int nMin = 0, int nMax = 0);
	int   GetDlgItemIntRange(UINT nID, int nMin = 0, int nMax = 0);
	void   SetDlgItemDoubleRange(UINT nID, double dbVal, double dbMin = 0, double dbMax = 0);
	double GetDlgItemDoubleRange(UINT nID, double dbMin = 0, double dbMax = 0);

	void SetEditTextLen(UINT nID,int nLimit) ;
	void SetComboBoxSelF(UINT nCmbID,float  fVal,int nDecCnt=6,LPCTSTR lpszPrefix=NULL,LPCTSTR lpszSuffix=NULL) ;
	void SetComboBoxSelD(UINT nCmbID,double fVal,int nDecCnt=14,LPCTSTR lpszPrefix=NULL,LPCTSTR lpszSuffix=NULL) ;
	void SetComboBoxSel(UINT nCmbID,int nItem,BOOL bByIndex=TRUE) ;
	void SetComboBoxSel(UINT nCmbID,LPCTSTR lpszItem) ;
	int  GetComboBoxSel(UINT nCmbID) ;
	void ResetComboBox(UINT nCmbID) ;

	void SetSliderReadOnly(UINT nSldID=-1,BOOL bSet=TRUE) ;
	void SetSliderRange(UINT nSldID,int nMin=0,int nMax=100);
	void GetSliderRange(UINT nSldID,int &nMin,int &nMax);
	void SetSliderBindItem(UINT nSldID,UINT nBindID,FLOAT fFector=1.0f);
	int  GetSliderPos(UINT nSldID);
	void SetSliderPos(UINT nSldID, int nPos);
	void SetProgessRange(UINT nSldID,int nMin=0,int nMax=100);
	void GetProgessRange(UINT nSldID,int &nMin,int &nMax);
	int  GetProgessPos(UINT nSldID);
	void SetProgessPos(UINT nSldID, int nPos);

	//nBegin 0:COM -1:Baud -2:VERIFY -3:BITS -4:STOP BITS -5:FLOW CTRL
	void QFillComboBox(UINT nCmbID,int nBegin=0,LPCTSTR lpszPrefix=_T("COM"),int nFillCount=96,LPCTSTR lpszSuffix=_T(""));
	void QEmptyComboBox(UINT nCmbID) ;
	void QEnumCOMPorts(UINT nCmbID);
	void QFillComboBoxString(UINT nCmbID,LPCTSTR *pszItems,int nForm=0,int nTo=0xFFFF) ;
	void QFillComboBox(UINT nCmbID,CStringArray&arrItems,int nForm=0,int nTo=0xFFFF) ;
	void QFillComboBoxInt(UINT nCmbID,int nCount,int nForm=0,int nStep=1) ;
	void QInsertComboBoxItem(UINT nCmbID,LPCTSTR lpszItem,int nAfterItem=-1) ;
	void QInsertComboBoxItem(UINT nCmbID,int nItemValue,int nFmtLen,LPCTSTR lpszPre=_T(""),int nAfterItem=-1) ;
	void QInsertComboBoxUniqueItem(UINT nCmbID,LPCTSTR lpszItem) ;
	int  QGetComboBoxAllItems(UINT nCmbID,CStringArray&arrRets) ;
	void QGetComboBoxAllItems(UINT nCmbID,CString&strRet,LPCTSTR lpszDiv=_T(";")) ;
	void QSaveComboBoxAllItemsToIni(UINT nCmbID,LPCTSTR lpszIniFile,LPCTSTR lpszSection,LPCTSTR lpszItemName) ;
	void QLoadComboBoxItemsFromIni(UINT nCmbID,LPCTSTR lpszIniFile,LPCTSTR lpszSection,LPCTSTR lpszItemName,int nLoadCount=-1,BOOL bAppendToCombox=FALSE) ;
	void QSetItemTextToItem(UINT nFromID,UINT nToID) ;	
	void QInsertTextToEdit(UINT nEditID,LPCTSTR lpszText) ;

	CListCtrl *GetListCtrl(UINT nListID) ;
	CListBox  *GetListBox(UINT nListID) ;
	CComboBox *GetComboBox(UINT nCmbID) ;

	CMyEdit     *GetMyEdit(UINT nEditID) ;
	CUxButton   *GetMyButton(UINT nBtnID) ;
	CMyListCtrl *GetMyListCtrl(UINT nListID) ;
	CMyListBox  *GetMyListBox(UINT nListID) ;
	CMyComboBox *GetMyComboBox(UINT nCmbID) ;
	CMyCheckButton *GetMyCheckButton(UINT nBtnID) ;
	CMyProgressCtrl *GetMyProgessCtrl(UINT nPrgID) ;
	CMySliderCtrl   *GetMySliderCtrl(UINT nSldID) ;
	CLabel *GetMyLabel(UINT nLabID, BOOL bSetFlat=FALSE);

 	//1:(_T("yyyy-MM-dd HH:mm:ss")) ;
	//2:(_T("yyyy-MM-dd HH:mm")) ;
	//3:(_T("HH:mm:ss"))
	//4:(_T("HH:mm")) ;
	CDateTimeCtrl *GetDateTimeCtrl(UINT nDTID,DWORD dwSetFormat=0) ;
	DWORD  GetDateTime(UINT nDTID) ;
	void   GetDate(UINT nDTID,int *pYear=NULL,int *pMonth=NULL ,int *pDay=NULL) ;
	void   GetTime(UINT nDTID,int *pHour=NULL,int *pMintue=NULL,int *pSecond=NULL) ;

	void   SetDateTime(UINT nDTID,DWORD dwTime) ;
	void   SetDate(UINT nDTID,int nYear=-1,int nMonth =-1 ,int nDay=-1) ;
	void   SetTime(UINT nDTID,int nHour=-1,int nMinute=-1 ,int nSecond=-1) ;

	void RoundDlgItem(UINT nID,int nRadius,CDC *pDC,COLORREF lpFillClr=RGB(255,255,255)) ;
	
	void SetListCtrlCheck(UINT nListID,BOOL bCheckBox=TRUE) ;
	void SetListCtrlCheck(CListCtrl *pList,BOOL bCheckBox=TRUE) ;
	void SetListCtrlIndex(UINT nListID,int nBegin=1,int nCol=0,LPCTSTR lpszPreFfix=_T(""),int nItemCount=-1) ;
	void SetListCtrlIndex(CListCtrl *pList,int nBegin=1,int nCol=0,LPCTSTR lpszPreFfix=_T(""),int nItemCount=-1) ;

	int  GetListCtrlSelCount(CListCtrl *pList,BOOL bCheckSel=TRUE) ;
	int  GetListCtrlSelCount(UINT nID,BOOL bCheckSel=TRUE) ;
	int  GetListCtrlSelectedItems(CListCtrl *pList,CArray<int,int>&arrItems,BOOL bRevSave=FALSE) ;
	int  GetListCtrlSelectedItems(UINT nListCtrlID,CArray<int,int>&arrItems,BOOL bRevSave=FALSE) ;
	int  GetListCtrlCheckedItems(CListCtrl *pList,CArray<int,int>&arrItems,BOOL bRevSave=FALSE) ;
	int  GetListCtrlCheckedItems(UINT nListCtrlID,CArray<int,int>&arrItems,BOOL bRevSave=FALSE) ;
	void DelListCtrlSelItem(UINT nID,BOOL bDelChecked=FALSE) ;
	void DelListCtrlSelItem(CListCtrl *pList,BOOL bDelChecked=FALSE) ;

	void SelListCtrlItems(CListCtrl *pList,DWORD dwFlag=0) ;
	void CheckedListCtrlItems(CListCtrl *pList,DWORD dwFlag=0) ;
	void SetListCtrlIndex(CListCtrl *pList,int nStart=1,int nCol=0,int nLen=2,CHAR cPad=' ',BOOL bHexFmt=FALSE);

	void SelListCtrlItems(UINT nListCtrlID,DWORD dwFlag=0) ;
	void CheckedListCtrlItems(UINT nListCtrlID,DWORD dwFlag=0) ;
	void SetListCtrlIndex(UINT nListCtrlID,int nStart=1,int nCol=0,int nLen=2,CHAR cPad=' ',BOOL bHexFmt=FALSE);

	void Show(DWORD dwShow=1) ; //0 Hide 1 show 2 SetCenter ;
	void SetTopMost(BOOL bSetTop=TRUE);
	void SendCmdMsg(WPARAM wParam,LPARAM lParam=0,BOOL bSend=FALSE) ;
	void SetAsMainDlg() ;

	BOOL IsDlgItemVisible(UINT nID) ;
	BOOL IsDlgItemEnabled(UINT nID) ;
	BOOL IsDlgItemClass(UINT nID,LPCTSTR lpszClassName) ;
	BOOL IsDlgItemClass(UINT nID,DWORD dwType) ;
	DWORD GetDlgItemClass(UINT nID) ;
	CString GetDlgItemClassName(UINT nID) ;
	void SetDlgEditPasswordStyle(UINT nID,BOOL bSet=TRUE) ;
	void ShowDlgItems(UINT *pItemIDs,int nCount,BOOL bToShow=TRUE) ;
	void ShowDlgItems(CWnd  **pItems ,int nCount,BOOL bToShow=TRUE) ;
	void ShowDlgItems(CArray<UINT,UINT>&arrItemIDs,BOOL bToShow=TRUE) ;
	void ShowDlgItems(CArray<CWnd*,CWnd*>&arrItems  ,BOOL bToShow=TRUE) ;

	void SetDlgItemsSize(UINT *pItemIDs,int nCount,int nXSize,int nYSize) ;
	void SetDlgItemsSize(CWnd  **pItems,int nCount,int nXSize,int nYSize) ;
	void SetDlgItemsSize(CArray<UINT,UINT>&arrItemIDs,int nXSize,int nYSize) ;
	void SetDlgItemsSize(CArray<CWnd*,CWnd*>&arrItems,int nXSize,int nYSize) ;

	void ListDlgItems(UINT *pItemIDs,int nCount,int nXPos,int nYPos,int nGap=5,BOOL bIsHDir=TRUE,int nDirSize=0) ;
	void ListDlgItems(CWnd **pItemls,int nCount,int nXPos,int nYPos,int nGap=5,BOOL bIsHDir=TRUE,int nDirSize=0) ;
	void ListDlgItems(CArray<UINT,UINT>&arrItemIDs,int nXPos,int nYPos,int nGap=5,BOOL bIsHDir=TRUE,int nDirSize=0) ;
	void ListDlgItems(CArray<CWnd*,CWnd*>&arrItems,int nXPos,int nYPos,int nGap=5,BOOL bIsHDir=TRUE,int nDirSize=0) ;

	void SetHoldButton(CArray<CUxButton *,CUxButton *>&arrBtns,CUxButton *pToHoldBtn) ;
	void SetHoldButton(CArray<UINT,UINT>&arrBtnIDs,UINT dwToHoldBtnID) ;
	void SetHoldButton(UINT *pBtnIDs,int nCount,UINT dwToHoldBtnID) ;
	void SetButtonIcon(UINT dwBtnID,CImageList *pImgList,int nIndex=0) ;
	void SetButtonIcon(UINT dwBtnID,LPCTSTR lpszNorIco=NULL,LPCTSTR lpszOvrIco=NULL,LPCTSTR lpszHoldIco=NULL) ;
	void SetItemDrawFrame(UINT dwItemID,BOOL bToAdd=TRUE) ;

	BOOL GetLabelCheck(UINT dwLabelID) ;
	CLabel *SetLabelCheck(UINT dwLabelID,BOOL bChecked=TRUE) ;
	CLabel *SetLabelCheckMode(UINT dwLabelID,DWORD dwCheckMode=1,BOOL bReadOnly=FALSE) ;//1 Radio 2 Check
	CLabel *SetLabelCheckColor(UINT dwLabelID,DWORD clrChecked=NULL,DWORD clrUnChecked=NULL) ;
	CLabel *SetLabelCheckImg(UINT dwLabelID,LPCTSTR lpszCheckedImg=NULL,LPCTSTR lpszUnCheckedImg=NULL) ;
	CLabel *SetLabelCheckChar(UINT dwLabelID,LPCTSTR lpszCheckedChar=NULL,LPCTSTR lpszUnCheckedChar=NULL) ;
	CLabel *SetLabelBKImg(UINT dwLabelID,LPCTSTR lpszBKImg1=NULL,LPCTSTR lpszBKImg2=NULL,BOOL bHideTxt=FALSE) ;
	CLabel *SetLabelHold(UINT dwLabelID,BOOL bHode=FALSE) ;
	CLabel *SetLabelBackColor(UINT dwLabelID,DWORD dwColor=-1,BOOL bColorPick=TRUE,BOOL bShowRGBText=TRUE,BOOL bHexFormat=TRUE) ;
	DWORD GetLabelBackColor(UINT dwLabelID) ;

	void SetDlgItemHold(UINT nID,BOOL bSetHold=TRUE) ;
	BOOL GetDlgItemHold(UINT nID) ;
	void SetDlgItemHoldText(UINT nID,LPCTSTR lpszHoldText) ;
	void SetDlgItemClickHold(UINT nID,BOOL bSet=TRUE) ;

	int  AddFillRect(int nPosX,int nPosY,int nW,int nH,int nBorderThickness=1,DWORD clrBorder=RGB(255,255,255),int nFillClrCnt=0,DWORD *pClrGroup=NULL,BOOL bFillHMode=FALSE) ;
	int  AddDrawLine(int nX1,int nY1,int nX2,int nY2,int nLineThickness=1,DWORD dwLineStyle=PS_SOLID,DWORD clrBorder=RGB(255,255,255)) ;
	int  AddDrawText(int nPosX,int nPosY,LPCTSTR lpszTxt,int nFontSize=0,int nBold=400,LPCTSTR lpszFontName=NULL,DWORD clrText=RGB(0,0,0),DWORD clrBK=0xFFFFFFFF,float fAngle=0,CFont *pTFont=NULL) ;
	int  AddDrawImage(int nPosX,int nPosY,LPCTSTR lpszImg,int nWidth=0,int nHeight=0,DWORD clrBK=0xFFFFFFFF,float fAngle=0) ;

	void SetDlgEditText(UINT nID,LPCTSTR lpszText,BOOL bKeepSel=TRUE) ;
	void CopyDlgItemText(UINT nID) ;

	BOOL RemoveOwndrawCtrl(UINT nCtrlID) ;
	void SetFullScreen(BOOL bSet=TRUE) ;
	void QSetTimer(int nIDEvent,int nInterval=0) ;

	void ClipDlgItemDC(CDC *pDC,UINT dwItemID) ;
	void ClipDlgItemDC(CDC *pDC,CWnd *pWnd) ;
	void PutDlgItemInto(UINT dwItemID,UINT dwInItemID,DWORD dwFlag,int nMargin) ;
	void CombineDlgItem(UINT dwItemID,UINT dwRelItemID,int nMargin) ;

	void SetDlgItemWheelValue(UINT dwItemID,DWORD dwType=0,double dbStep=1) ;
	virtual void SetDlgItemText(UINT dwItemID,LPCTSTR lpszText) ;
	virtual void SetDlgItemInt(UINT dwItemID,int nValue) ;
	virtual CWnd *GetDlgItem(UINT dwItemID,BOOL bToSubIfNo=TRUE) ;

	void QMessageBox(LPCTSTR lpszTip,int nValue) ;
	void QMessageBox(LPCTSTR lpszTip,double dbValue) ;

	CString QBrowseFile(UINT nSetToItemID=0,BOOL bToOpen=TRUE) ;
	CString QBrowseFolder(UINT nSetToItemID=0) ;

	SHORT    m_zDelta ;
	DWORD    m_dwRedrawCtrl ;
	COLORREF m_clrBK ;
	COLORREF m_clrFR ;
	CBrush   m_brBK ;
	CBrush   m_brFR ;
	COLORREF m_clrFrame ;
	BOOL     m_bDrawTBar;
	float    m_fFontSize ;
	CString  m_strBKImgFile ;
	BOOL     m_bTrimZeroVal ;

	int    m_nTitleBarH ;
	DWORD  m_dwLastDlgID;
	DWORD  m_dwClkEditID;
	BOOL   m_bEnableROEditClr ;
	BOOL   IsReadOnlyEditCtrl(int nEditID);
	void   SetEditBKColor(COLORREF clrEdit);
	void   SetFrameColor(COLORREF clrFrm );
	void   SetBKGradColors(COLORREF *pColors,DWORD dwCount,BOOL bIsVertMode=TRUE) ;
	void   SetBKGradColors(COLORREF clrBk1,COLORREF clrBk2,BOOL bIsVertMode=TRUE) ;
	void   SetBKGradColors(DWORD dwHMode,...) ;

	void   SetCOMItems(UINT nPort,UINT nBaud,UINT nVery=0,UINT nData=0,UINT nStop=0,UINT nFlow=0) ;
	void   SetCOMSels(UINT nPort=0,UINT nBaud=7,UINT nVery=0,UINT nData=0,UINT nStop=0,UINT nFlow=0) ;
	void   GetCOMSels(UINT &nPort,UINT &nBaud,UINT &nVery,UINT &nData,UINT &nStop,UINT &nFlow) ;
	BOOL   OpenCOMEasy(CEasyComPort *pCom) ;
	
	void   SetCOMItemsEx(int nGroup,UINT nPort,UINT nBaud,UINT nVery=0,UINT nData=0,UINT nStop=0,UINT nFlow=0) ;
	void   SetCOMSelsEx(int nGroup,UINT nPort=0,UINT nBaud=7,UINT nVery=0,UINT nData=0,UINT nStop=0,UINT nFlow=0) ;
	void   GetCOMSelsEx(int nGroup,UINT &nPort,UINT &nBaud,UINT &nVery,UINT &nData,UINT &nStop,UINT &nFlow) ;
	void   SaveCOMSet(int nGroup);
	void   LoadCOMSet(int nGroup);
	BOOL   OpenCOMEasyEx(int nGroup,CEasyComPort *pCom) ;
	CMyComboBox *m_pCOMSel ;

	int    m_nCOMGroup ;
	void   ShowCOMPortList(UINT nItemID,int nType=0,int nSelItem=0,int nCount=32,BOOL bJustInit=FALSE) ;

	BOOL  m_bDragable;
	BOOL  m_bFShowMaxBtn;
	BOOL  m_bFShowMinBtn;
	BOOL  m_bFShowTopBtn;
	BOOL  m_bFShowClsBtn;
	BOOL  m_bRedrawWinFrm ;
	BOOL  m_bSetButtonDefImg ;
	BOOL  m_bAutoAdjFontSize ;
	BOOL  m_bTransChildCmd ; //OnCommand
	UINT  m_nDlgID ;
	UINT  m_nNoRewaitIDs[10] ;

	void DrawDialog(CDC *pDRDC,BOOL bNoFillBk=FALSE) ;
	void BuildGroupBrush(CDC *pDC) ;
	void DisableIME(BOOL bDisable = TRUE);
	CWnd *CreateControlPanel(DWORD dwDialogTempID,BOOL bShow=TRUE) ;

	BOOL IsCursorInDlgItem(CWnd* pWnd);
	BOOL IsCursorInDlgItem(UINT nID);

	void SetSpecialID(int nStartID=-1,int nSetTopID=-1) ;

	void SetCtrlOwnDrawFlag(DWORD dwCtrlType=0xFFFF,BOOL bSet=TRUE);
	void SetCheckBoxToolTipTxt(DWORD dwChkBoxID=-1,LPCTSTR lpTipTxt=NULL);
	void EnableCheckBoxToolTip(DWORD dwChkBoxID=-1,BOOL bEnable=true);
	void SetCheckBoxImagePos(DWORD dwChkBoxID=-1,int nImgPosX=-1,int nImgPosY=-1) ;
	void SetCheckBoxImageSize(DWORD dwChkBoxID=-1,int nWidth=-1,int nHeight=-1) ;
	void SetCheckBoxImageToRight(DWORD dwChkBoxID=-1,BOOL bSetToRight=TRUE,BOOL bHideText=FALSE) ;
	void SetCheckBoxNormalImage(DWORD dwChkBoxID=-1,LPCTSTR lpszCheckedImg=_T(""),LPCTSTR lpszUncheckImg=_T(""),BOOL bHideTxt=FALSE) ;
	void SetCheckBoxHoverImage(DWORD dwChkBoxID=-1,LPCTSTR lpszCheckedHoverImg=_T(""),LPCTSTR lpszUncheckHoverImg=_T(""),BOOL bHideTxt=FALSE) ;

	TCHAR m_szTrayTip[256] ;
	HICON m_hTrayIcon ;
	DWORD m_dwTrayMsg ;
	BOOL  m_bTrayAuto ;
	NOTIFYICONDATA  *m_pTray;
	BOOL SetTaskBarTrayIcon(DWORD dwType=NIM_DELETE,LPCTSTR lpszTipText=NULL,DWORD dwNotifyMsg=0,HICON hIcon=NULL);

	virtual int OnCommonCOMDataIN(void *pData,int nDataLen,void *pCom) ;
	virtual int OnCommonSocketDataIN(void *pData,int nDataLen,void *pSocket) ;
	virtual int OnCommonSocketAccept(SOCKET nSocket,void *pInAddr) ;

	Bitmap*m_pSuperBK;
	CBrush m_SuperBK ;
	BOOL m_bUseParentBK; // WS_CHILD

private:
	void EnumDlgButtons() ;
	void ChangeMaxStauts();
	void ShowSystemMenu() ;
	void ResetBtnsPostion();
	void PutDlgItemPos(UINT nID) ;
	void PutDlgItemPos(CWnd *pWnd) ;

	HANDLE m_hIMMC;
	BOOL  m_bMaxStatus	; 
	BOOL  m_bTopStatus	; 
	BOOL  m_bResizeAble ;
	BOOL  m_bEditSetUpdate ;
	CRect      m_rcIcon   ;		//Õº±ÍŒª÷√
	CMenu     *m_pSysMenu ;
	CUxButton *m_pBtnCls  ;
	CUxButton *m_pBtnMin  ;
	CUxButton *m_pBtnMax  ;
	CUxButton *m_pBtnTop  ;
	DWORD      m_dwOrgStyle ;
	DWORD      m_dwLangID ;
	CIniAX    *m_pLangIni ;

	COLORREF m_clrGrdBK[20] ;
	DWORD    m_dwGrdClrCnt   ;
	BOOL     m_bIsGrdVertMode;
	COLORREF m_clrEditFCFrm ;

	int  m_nCOMItem ;
	int  m_nCOMType ;

	int  m_nCOMSels[6] ;
	int  m_nCOMIDs[6] ;
	CStringArray m_COMArray ;
	EasyCOMSetting m_COMs[32] ;

	int m_nSetTopID ;
	int m_nAutoStartID ;
	
	CBrush m_Editbr ;
	CArray<int,int>m_arrROEditIDs ;
	CArray<int,int>m_arrTipEdits ;
	CArray<int,int>m_arrBtnIDs ;
	CArray<int,int>m_arrCRBIDs ;
	CArray<int,int>m_arrLabIDs ;
	CArray<CWnd *,CWnd *>m_arrSliders ;
	CArray<CWnd *,CWnd *>m_arrChkBoxs ;
	CArray<CWnd *,CWnd *>m_arrCapBtns ;
	CArray<CWnd *,CWnd *>m_arrDrawFrms ;
	CArray<CWnd *,CWnd *>m_arrRedraw ;
	CArray<CWnd *,CWnd *>m_arrPanels ;
	CArray<GroupBrush *,GroupBrush *>m_arrGBoxBR ;
	CArray<GroupColor *,GroupColor *>m_arrItemClr ;

	
	CPtrList m_TipEdits;
	CPtrList m_FillRects;
	CPtrList m_DrawLines;
	CPtrList m_DrawTexts;
	CPtrList m_DrawImages;
	CPtrList m_EditFrmClr;
	CPtrList m_WheelValue;
	CPtrList m_MyMargins;
	CPtrList m_SliderBind;

	CArray<CWnd *,CWnd *>m_arrEdits ;

	CFont *m_pNewFont ;

	CPoint m_ptClk ;

	CArray<CWnd *,CWnd *>m_arrOwnDraws ;
	CWnd *PickupOwndrawCtrl(UINT nCtrlID,DWORD dwType=0x80000000);
	CWnd *BuildOwnrawCtrl(UINT nCtrlID,DWORD dwType);

	//{{AFX_DATA(CMyDialog)
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMyDialog)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CMyDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDropFiles(HDROP hDropInfo);	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnTaskbarCreated(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CMyDialog *g_pMaigDlg;

