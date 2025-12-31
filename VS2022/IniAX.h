// IniAX.h

#if !defined(AFX_INIAX_H__02C8EF53_D999_4AFA_8796_66C7B09754BA__INCLUDED_)
#define AFX_INIAX_H__02C8EF53_D999_4AFA_8796_66C7B09754BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniAX  
{
public:
	CIniAX(LPCTSTR lpszFile=NULL,LPCTSTR lpszSection=NULL,LPCTSTR lpszArrayName=NULL);
	virtual ~CIniAX();

	void SetFile(LPCTSTR lpszFile=NULL,LPCTSTR lpszSection=NULL,LPCTSTR lpszArrayName=NULL) ;
	void SetSection(LPCTSTR lpszSection) ;

	void SetArrayName(LPCTSTR lpszArrayName) ;

	int  GetInt(LPCTSTR lpszName,int nDefault=0,BOOL bHexFormat=FALSE) ;
	void SetInt(LPCTSTR lpszName,int nValue,BOOL bHexFormat=FALSE) ;
	int  GetArrayInt(int nItem,int nDefault=0,BOOL bHexFormat=FALSE) ;
	void SetArrayInt(int nItem,int nValue,BOOL bHexFormat=FALSE) ;

	float GetFloat(LPCTSTR lpszName,float fDefault=0.0) ;
	void  SetFloat(LPCTSTR lpszName,float fValue) ;
	float GetArrayFloat(int nItem,float fDefault=0.0) ;
	void  SetArrayFloat(int nItem,float fValue) ;

	double GetDouble(LPCTSTR lpszName,double dbDefault=0.0) ;
	void   SetDouble(LPCTSTR lpszName,double dbValue) ;
	double GetArrayDouble(int nItem,double dbDefault=0.0) ;
	void   SetArrayDouble(int nItem,double dbValue) ;

	void GetArrayString(int nItem,TCHAR *pszRet,LPCTSTR lpszDefault=NULL) ;
	void GetArrayString(int nItem,CString&strRet,LPCTSTR lpszDefault=NULL) ;
	void SetArrayString(int nItem,LPCTSTR lpszValue) ;

	TCHAR*GetString(LPCTSTR lpszName,LPCTSTR lpszDefault=NULL) ;
	void SetString(LPCTSTR lpszName,LPCTSTR lpszValue) ;

	DWORD GetBinary(LPCTSTR lpszName,BYTE **pValue) ;
	void  SetBinary(LPCTSTR lpszName,BYTE *pValue ,DWORD dwSize) ;
	DWORD GetArrayBinary(int nItem,BYTE **pValue) ;
	void  SetArrayBinary(int nItem,BYTE *pValue ,DWORD dwSize) ;

private:	
	CString m_strFile ;
	CString m_strSection;
	CString m_strArrayName;
	CString&MakeItem(int nItem) ;
};

#endif 
