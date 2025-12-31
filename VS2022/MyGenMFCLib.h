
#include "MyInfo.h"

#include <ATLCONV.H>
#include <AFXTEMPL.H>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")



#ifdef _UNICODE

#ifdef _DEBUG
#pragma comment(lib,"MyGenMFCLibD.lib")
#else
#pragma comment(lib,"MyGenMFCLib.lib")
#endif

#else

#ifdef _DEBUG
#pragma comment(lib,"MyGenMFCLibD.lib")
#else
#pragma comment(lib,"MyGenMFCLib.lib")
#endif

#endif

#define   CDialog    CMyDialog
#define   CDialogEx  CMyDialog
