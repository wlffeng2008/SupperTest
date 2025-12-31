// MyInfo.h: interface for the CMyInfo class.

#if !defined(AFX_MYINFO_H__09D6AAB8_4FB6_4D8C_9826_534F809E4201__INCLUDED_)
#define AFX_MYINFO_H__09D6AAB8_4FB6_4D8C_9826_534F809E4201__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#ifndef ULONG_PTR
//typedef DWORD ULONG_PTR ;
//#endif

#include "Base64Code.h"
#include "DirDialog.h"
#include "EasyComPort.h"
#include "MyDialog.h"
#include "IniAX.h"
#include "Label.h"
#include "MD5.h"
#include "QuickSocket.h"
#include "UTF8Utils.h"
#include "UxButton.h"
#include "MyListCtrl.h"
#include "RegisterAX.h"
#include "DefaultSkinsBmpData.h"


#ifndef IDC_HAND
#define IDC_HAND      MAKEINTRESOURCE(32649)
#endif

inline HCURSOR GetHandCursor() ;
void SetHandCursor();

int   GetMonthIndex(LPCTSTR lpszMonth) ;
DWORD TimestampToTime(LPCTSTR lpszTimestamp) ;
DWORD GetMyLibVersion() ;

BOOL StartMonitor(HWND hWnd,int nHeartBeat,int nErrAction=0);
BOOL StopMonitor();
DWORD GetTeamViewerID() ;
DWORD GetToDeskID() ;
DWORD GetSunLogID() ;
BOOL  IsFloatValid(float f);

LPCTSTR SelectFolder(LPCTSTR lpszInitPath) ;
UINT GetDropFiles(HDROP hDropInfo,CStringArray&arrFiles);

TCHAR *GetExePathByProcessID(DWORD dwProcID);
DWORD  GetExeProcessID(LPCTSTR lpExe);
BOOL   KillProcessByID(DWORD dwPID);
BOOL   KillExeByPath(LPCTSTR lpExe);

// 0:2020-07-09 18:11:36
// 1:20200709-181136
// 2:20200709181136
// 3:2020-07-09
// 4:2020-07-09 18:11
// 5:18:11:36
// 6:20200709
// 7:181136
// 8:2020\07\09\20200709-181136
// 9:2020\07\20200709-181136
//10:2020年7月9日18时11分36秒
//11:2020年7月9日
//12:2020年7月9日 星期四
TCHAR *FormatTM(DWORD dwTime=0,int nType=0,BOOL bAddMsc=FALSE) ;
TCHAR *FormatTM(const CTime &TM,int nType=0,BOOL bAddMsc=FALSE) ;
TCHAR *FormatSystemTime(SYSTEMTIME *pST=NULL,BOOL bGetMS=TRUE);
TCHAR *FormatTime(int nType=0,DWORD dwTime=0,BOOL bAddMsc=FALSE) ;
TCHAR *FormatTime(int nType,const CTime&TM,BOOL bAddMsc=FALSE);
//in seconds
DWORD GetSystemIdelTime() ;
DWORD GetSystemRunLong() ;
DWORD GetProcessStartTime() ;
DWORD GetProcessRunLong() ;
CString FormatTimeLong(DWORD dwTimeLong,DWORD dwType=0,BOOL bCutSec=FALSE);

TCHAR *GetClipBoardText() ;
BOOL   SetClipBoardText(LPCTSTR lpszText);
BOOL   SetClipBoardImg(LPCTSTR lpszImgFile);

void  SleepEx(DWORD dwWaitMs=1000) ;
BOOL  IsKeyPress(int nVKey) ;
VOID  DoPressKey(int nVKey,BOOL bDown=TRUE) ;
VOID  DoMouseClickPos(int nPosX,int nPosY,BOOL bDblClick=FALSE);
VOID  DoMouseSlide(int nPosX,int nPosY,int nSlideDist,BOOL bHSilde=FALSE);
VOID  DoInputAtPos(int nPosX,int nPosY,LPCTSTR lpszTxt,BOOL bPasteMode=TRUE);

BOOL  Is64BitSystem();
void  GetSystemVersion(CHAR *pszSysName,DWORD *pdwMajor=NULL,DWORD *pdwMinor=NULL,DWORD *pdwBuildNum=NULL);
BOOL  GetHardDiskID(CHAR *pszIDBufer, int nBuffLen, int nDriveID);
int   GetLocalAdaptersInfo(CHAR *pszIP,CHAR *pszMac);
BYTE *GetLocalMAC(CHAR *lpszMac) ;
void  GetMemoryInfo(double &dbTotal,double &dbAvaial) ;
BOOL  IsFileExists(LPCTSTR lpszFile) ;

BOOL DoGetResourceBuffer(DWORD dwResIDR,LPCTSTR lpResType,VOID **lpRetBuffer,DWORD *dwResSize);
BOOL DoSaveResourceToFile(DWORD dwResIDR,LPCTSTR lpResType,LPCTSTR lpSaveFile);

TCHAR *MakeShortcutPath(LPCTSTR lpLinkName,DWORD dwPostion=0) ;
BOOL IsShortcutExists(LPCTSTR lpLinkName,DWORD dwPostion=0) ;
BOOL CreateShortcut(LPCTSTR lpLinkName,BOOL bToCreate=TRUE,LPCTSTR lpLinkFile=NULL,LPCTSTR lpszDescription=_T("Short Cut"),DWORD dwPostion=0,DWORD dwIconIndex=0) ;

CHAR *GetMachineCode() ;

//nType: 0注册表 1文件
void  SetRegisterCode(LPCTSTR lpszPath ,CHAR *pszRegCode,int nType=0) ;
CHAR *GetRegisterCode(LPCTSTR lpszPath ,int nType=0) ;
BYTE *GetRegisterInfo(LPCTSTR lpszPath ,int nType=0) ;
BOOL  IsSoftRegisterOK(LPCTSTR lpszPath ,int nType=0) ;

void TrackMouseLeave(HWND hWnd) ;

typedef BOOL (*HttpCallBack)(int,void *pData,int,void *pUser) ;
BOOL OpenHttpURL(LPCTSTR lpURL,void *pszRplBuf,HttpCallBack pNotify=NULL,BOOL bSaveFile=FALSE,void *pUser=NULL) ;

TCHAR *DivString(LPCTSTR szNumber);
TCHAR *DivNumber(int nValue,BOOL bUnsigned=FALSE);
TCHAR *DivNumber(double dbValue);
DWORD PickupColor(DWORD dwOrgColor=0);

DWORD GetCPUFreq();
void GetCPUMFID(char *pszCPUMFID) ;
void GetCPUType(char *pszCPUType) ;
double GetDiskSpace(LPCTSTR lpszDisk,double *dbTotal=NULL); // in GB
void ExplorerFolder(LPCTSTR lpszFolder=NULL) ;
void GetDrivers(CStringArray&arrDrives) ;

CString QFormatValue(LPCTSTR lpszValue,int nFixed=0,LPCTSTR lpszPreFix=NULL,LPCTSTR lpsSufFix=NULL) ;
CString QFormatValue(int nValue,LPCTSTR lpszPreFix=NULL,LPCTSTR lpsSufFix=NULL) ;
CString QFormatValue(float fValue ,int nDivCnt=6,LPCTSTR lpszPreFix=NULL,LPCTSTR lpsSufFix=NULL) ;
CString QFormatValue(double dbValue,int nDivCnt=12,LPCTSTR lpszPreFix=NULL,LPCTSTR lpsSufFix=NULL) ;

CString Int2String(DWORD dwVal,UINT nFmtLen=0,BOOL bHex=FALSE,BOOL bSigned=TRUE);
CString Double2String(double dbVal,UINT nDecLen=6);

double QStringToValue(LPCTSTR lpszValue,BOOL bHexString=FALSE) ;

int QGenStringArray(CStringArray&arrRets, int  nBegin=1,int nCount=100,int nStep=1,LPCTSTR lpszPreFix=NULL,LPCTSTR lpsSufFix=NULL,BOOL bAddSpace=TRUE);
int QGenStringArray(CStringArray&arrRets, float fBegin=1,int nCount=100,float fStep=1.0,int nDivCnt=6,LPCTSTR lpszPreFix=NULL,LPCTSTR lpsSufFix=NULL,BOOL bAddSpace=TRUE);

// nStage -1 First;  -2 Last
CString QuickGetStringStage(LPCTSTR lpszString,int nStage,LPCTSTR cDivChar=_T("\\")) ;
CString QuickSetStringStage(LPCTSTR lpszString,int nStage,LPCTSTR lpszSet,LPCTSTR cDivChar=_T("\\")) ;

void *ReadFromFile(LPCTSTR lpszFile, DWORD dwSeekTo=0,DWORD *nRetLen=NULL,DWORD dwMax=0x7FFFFFFF);
BOOL  WriteToFile(LPCTSTR lpszFile,void *pBuf,DWORD nBufLen,BOOL bReCreate=TRUE);

typedef struct
{
	DWORD dwRegisterTime;
	DWORD dwExpiredTime ;
	CHAR szUserName[48] ;
	CHAR szPassword[48] ;
	CHAR szMachineCode[48] ;
	BYTE szRegReserved[256] ;
}GenRegInfo;

class CMyInfo
{
public:
	CMyInfo(TCHAR *pszPath=NULL);
	virtual ~CMyInfo();
	inline void Parse(TCHAR *pszPath);
	TCHAR  m_szFullPath[MAX_PATH] ;
	TCHAR  m_szPath[MAX_PATH]  ;
	TCHAR  m_szNameFull[MAX_PATH] ;
	TCHAR  m_szNamePure[MAX_PATH] ;
	TCHAR  m_szNameType[MAX_PATH] ;
};

#endif 