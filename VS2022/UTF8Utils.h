
#ifndef __UTF8UTILS_H__
#define __UTF8UTILS_H__

CHAR *UTF8Encode(LPCSTR lpszSrc);
CHAR *UTF8Decode(LPCSTR lpszUTF8);

WCHAR *UTF8ToWide(LPCSTR lpszUTF8);
CHAR *WideToUTF8(WCHAR* lpszWide);

WCHAR *CHARToWide(LPCSTR lpszUTF8);
CHAR *WideToCHAR(WCHAR* lpszWide);

wchar_t *FF_A2W(LPCSTR  lpszSrc) ;
CHAR    *FF_W2A(LPCTSTR lpszSrc) ;
BOOL IsUTF8String(const char *pszTxt);

#endif
