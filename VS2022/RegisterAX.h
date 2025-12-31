// RegisterAX.h

#if !defined(AFX_REGISTERAX_H__98332335_740E_4E47_8F08_0689B508E55B__INCLUDED_)
#define AFX_REGISTERAX_H__98332335_740E_4E47_8F08_0689B508E55B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <afxtempl.h>

typedef struct
{
	TCHAR szItemName[256] ;
	BYTE *pValueBuf ;
	DWORD dwValBufLen ;

}RegItem,*LPRegItem;

typedef enum
{
	TYPE_STR=1,
	TYPE_BIN=3,
	TYPE_INT=4,
	TYPE_OTH=0
}RDType;

class CRegisterAX
{
public:
	CRegisterAX(LPCTSTR lpDefKeyName = _T("SOFTWARE\\GenSoftWare\\SmallSystem"),HKEY hRootKey=HKEY_CURRENT_USER);
	virtual ~CRegisterAX();

	VOID  CloseKey() ;
	BOOL  OpenKey() ;
	HKEY  GetRootKey();
	VOID  SetRootKey(HKEY hRootKey=HKEY_CURRENT_USER);
	VOID *CreateRegItem();
	VOID  FreeRegItem(VOID *pItem);
	VOID  FreeRegItem(CArray<LPRegItem,LPRegItem>&arrItems);

	BOOL  SetKeyName(LPCTSTR lpszRegKey,BOOL bCreateIfNoExist=TRUE) ;
	VOID  GetKeyName(LPCTSTR lpszRegKey);

	BOOL  SetItemValue(LPCTSTR lpItem,VOID *pValue,DWORD  dwLen=sizeof(DWORD),DWORD dwType=TYPE_INT) ;
	BOOL  GetItemValue(LPCTSTR lpItem,VOID *pValue,DWORD *pdwLen=NULL,DWORD *pdwType=NULL) ;
	BOOL  DeleteItem(LPCTSTR lpItem) ;

	BOOL  EnumKeyValues(CArray<LPRegItem,LPRegItem>&arrValues,LPCTSTR lpRegKey=NULL);
	BOOL  EnumSubkeys(CStringArray&arrSubkeys,LPCTSTR lpRegKey=NULL);

	int  GetInt(LPCTSTR lpszName,int nDefault=0) ;
	void SetInt(LPCTSTR lpszName,int nValue) ;

	float GetFloat(LPCTSTR lpszName,float fDefault=0.0) ;
	void  SetFloat(LPCTSTR lpszName,float fValue) ;	
	double GetDouble(LPCTSTR lpszName,double dbDefault=0.0) ;
	void   SetDouble(LPCTSTR lpszName,double dbValue) ;

	TCHAR*GetString(LPCTSTR lpszName,LPCTSTR lpszDefault=NULL) ;
	void SetString(LPCTSTR lpszName,LPCTSTR lpszValue) ;

	BOOL GetBinary(LPCTSTR lpszName,BYTE **pValue) ;
	void SetBinary(LPCTSTR lpszName,BYTE *pValue ,DWORD dwSize) ;

private:
	HKEY    m_hKey ;
	HKEY    m_hRootKey ;
	CString m_strRegKey ;
};

#endif
