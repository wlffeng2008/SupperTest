// EasyComPort.h

#if !defined(AFX_SERIALCOM_H__D9C470BD_B1DF_43EB_91C3_6F3B851D9D72__INCLUDED_)
#define AFX_SERIALCOM_H__D9C470BD_B1DF_43EB_91C3_6F3B851D9D72__INCLUDED_
#pragma warning(disable:4786)

#if _MSC_VER > 1000
#pragma once
#endif

typedef enum
{
	CRC_0,
	CRC_8,
	CRC_16,
	CRC_32
}CRCType;

BYTE  *HexStringToBytes(LPCTSTR lpszStr,int&nRetLen,BOOL bRevered=FALSE) ;//0x,
LPCSTR BytesToHexString(BYTE *pHexBuf,int nLen,BOOL bRevered=FALSE,BOOL bToArray=FALSE) ;
BOOL  CheckCRCSum(BYTE *pBuf, WORD nLen,int nCRCType=CRC_8) ;
DWORD GetBufCRCSum(BYTE *pBuf, WORD nLen,int nCRCType=CRC_8) ;
VOID  AppBufCRCSum(BYTE *pBuf, WORD nLen,int nCRCType=CRC_8) ;

BOOL CheckCRC8( BYTE *pBuf, WORD nLen) ;
BOOL CheckCRC16(BYTE *pBuf, WORD nLen) ;
BOOL CheckCRC32(BYTE *pBuf, WORD nLen) ;

BYTE Get_CRC8_Sum(BYTE *pBuf,WORD nLen);
VOID App_CRC8_Sum(BYTE *pBuf,WORD nLen);

WORD Get_CRC16_Sum(BYTE const *pBuf,WORD nLen);
VOID App_CRC16_Sum(BYTE *pBuf,WORD nLen);

DWORD Get_CRC32_Sum(BYTE *pBuf,WORD nLen);
VOID  App_CRC32_Sum(BYTE *pBuf,WORD nLen);

WORD Get_ModBusCRC(const void *pData, WORD wSize);
void App_ModBusCRC(const void *pData, WORD wSize);

void *MB_MakeReadCmd(BYTE nID, WORD wAddr, WORD wCount=1); // Len =8
void *MB_MakeWriteCmd(BYTE nID, WORD wAddr, WORD wCount, void *pData); // Len = wCount*2 + 2
void *MB_MakeWriteCmd(BYTE nID, WORD wAddr, WORD wValue);

typedef BOOL (*ComDataCB)(void *,int, void *pUserData) ;


class CMyDialog ;
class CEasyComPort
{
public:
	CEasyComPort();
	virtual ~CEasyComPort();

	int GetMode() ;
	int GetPort() ;
	int GetBaud() ;
	void SetMode(int nMode,BOOL bReOpen=TRUE) ;
	void SetPort(int nPort,BOOL bReOpen=TRUE) ;
	void SetBaud(int nBaud,BOOL bReOpen=TRUE) ;
	void SetName(LPCTSTR lpszName) ;
	LPCTSTR GetName() ;

	BOOL ReOpen(int nMode=-1) ;
	BOOL Open(int nPort=1, int nBaud=CBR_9600, int nParity=NOPARITY, int nDatabits=8, int nStopsbits=ONESTOPBIT);
	BOOL Open(LPCTSTR lpszPort, int nBaud=CBR_9600, int nParity=NOPARITY, int nDatabits=8, int nStopsbits=ONESTOPBIT);
	void Close();
	BOOL IsOpen() ;
	BOOL Setup(DWORD dwInputSize=4096, DWORD dwOutputSize=4096);

	BOOL  Write(void *pData,WORD wLen,BOOL bAddtoList=FALSE,BOOL bWaitForReply=TRUE);
	BOOL  Write(LPCSTR lpszString,BOOL bAddtoList=FALSE,BOOL bWaitForReply=TRUE);
	void  SetCRCType(CRCType nType=CRC_8);
	DWORD WriteCRC(LPCVOID pBuffer,WORD wLen,BOOL bAddtoList=FALSE,BOOL bWaitForReply=TRUE) ;
	
	void  SetRecvPageSize(int nRecvPageSize=-1);
	void  SetRecvWaitTime(int nRecvWaitTime=-1);
	void  SetDataCB(ComDataCB pRecvData,int nRecvPageSize=-1,int nRecvWaitTime=-1);
	void  SetDataCBDialog(void *pDialog,int nRecvPageSize=-1,int nRecvWaitTime=-1);
	void *GetDataCBDialog() ;

private:
	int   m_nMode  ;
	void *m_pCOMAX ;
	HANDLE m_hRplEvt ;
	BOOL m_bEndWork ;

	int m_nPort ;
	int m_nBaud ;
	int m_nParity;
	int m_nDatabits ;
	int m_nStopsbits ;
	TCHAR m_szName[64] ;

	DWORD m_dwTimeout;
	DWORD m_nPageSize;
	CMyDialog *m_pDialog ;
	ComDataCB m_pDataCB ;

	void AddToList(void *pData,WORD wLen,BOOL bWaitForReply=TRUE) ;
	CPtrList m_COMBufList ;
	CRITICAL_SECTION m_cs ;
	static UINT ThreadSynWrite(LPVOID lpParam) ;
	void DoWriteSyn() ;
};


#endif
 

