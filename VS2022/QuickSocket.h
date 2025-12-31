
#ifndef __QUICKSOCKET__H__
#define __QUICKSOCKET__H__

#ifdef __cplusplus
extern "C" {
#endif

#define  MAX_QS_TIMEOUT    0x7FFFFFFF

#include <winsock.h>

typedef void (*SOCKET_ACCEPT_CALLBACK)(VOID *pListenSockInfo, SOCKET nNewInSock, SOCKADDR_IN *pInCLAddr, void *pUPDInData, DWORD dwUDPInDataLen);
typedef void (*SOCKET_DATAIN_CALLBACK)(VOID *pData, int nLen, SOCKET nSocket, void *pUserData);

typedef struct
{
	BOOL             bIsTCPMode   ;
	BOOL             bExit        ;
	BOOL             bBroadCast   ;
	WORD             wListenPort  ;
	DWORD            dwUDPRecvLen ;
	SOCKET           nServerSock  ;
	LPVOID           lpExtData    ;
	HANDLE           hEvtThreadOK ;
	SOCKET_ACCEPT_CALLBACK  lpDealWithCB ;

}ServerSockInfo;

BOOL   StartUpSock();
VOID   CleanupSock();
BOOL   StopServerSocket(SOCKET nSocket) ;
BOOL   QuickGetHostByName(LPCTSTR lpSrcName, TCHAR *pszRetIP, SOCKADDR_IN *pAddr=NULL, DWORD *pIPAdrr=NULL) ;
TCHAR *QGetLocalhostIP() ;

VOID*  QuickStartTCPServer(WORD wListenPort, SOCKET_ACCEPT_CALLBACK lpDealWithCB=NULL);
VOID*  QuickStartUDPServer(WORD wListenPort, BOOL bBoradCast=TRUE, SOCKET_ACCEPT_CALLBACK lpDealWithCB=NULL, DWORD dwProtoHeadLen=0);
BOOL   WaitSocketData(SOCKET nSocket, int nTimeout=1000, BOOL bWaitToRecv=TRUE);
SOCKET QuickConnectToTCP(WORD wServerPort, LPCTSTR lpServerIP=NULL);
SOCKET QuickSendToUDP(WORD wPort, VOID *pBuffer, DWORD dwSize=0, BOOL bRetSock=FALSE, LPCTSTR lpServerIP=NULL);
SOCKET AcceptTCPClient(SOCKET nListenSock, int nTimeout=MAX_QS_TIMEOUT, SOCKADDR_IN *pInAddr=NULL);

BOOL   SetSocketBufferSize(SOCKET nSocket,int nBufferSize=0xFFFF,DWORD dwFlags=3);
BOOL   SetSocketTimeOut(SOCKET nSocket, int nTimeout=MAX_QS_TIMEOUT,DWORD dwFlags=3);
int    ForceSend(SOCKET nSocket, void *pszBuf, int dwLen=0, int nTimeout=MAX_QS_TIMEOUT, BOOL bUDPFlag=FALSE, SOCKADDR_IN *pCLAddr=NULL);
int    ForceRecv(SOCKET nSocket, void *pszBuf, int dwLen, int nTimeout=15000, BOOL bUDPFlag=FALSE, SOCKADDR_IN *pCLAddr=NULL);

VOID   NotifySocketToEnd(WORD wPort, BOOL bIsTcpMode=FALSE);

#ifdef __cplusplus
}
#endif

#include "MyDialog.h"

class CMySocket: public CMySimpleThread
{
public:
	CMySocket() ;
	CMySocket(SOCKET nSocket, BOOL bIsUDP=FALSE) ;
	CMySocket(int nPort, BOOL bIsUDP, BOOL bServer, LPCTSTR lpszServerIP=_T("127.0.0.1")) ;
	virtual~CMySocket() ;

	void SetSocket(SOCKET nSocket, BOOL bIsUDP=FALSE) ;
	void SetSocket(int nPort, BOOL bIsUDP, BOOL bServer, LPCTSTR lpszServerIP=_T("127.0.0.1")) ;
	SOCKET GetSocket() ;
	void*GetFromAddr() ;

	virtual int  OnSimpleThreadLoopRun(int nWorkerID);
	virtual void OnTCPAccept(SOCKET nSocket,void *pInAddr) ;
	virtual void OnSocketDataIn(SOCKET nSocket,void *pInAddr,void *pData,int nDLen) ;
	void SetUDPBufSize(DWORD dwSize=128) ;
	void SetAsyncRecv(BOOL bAsync=TRUE) ;

	void SetDataInCallBack(SOCKET_DATAIN_CALLBACK pDataInCB) ;
	void SetAcceptCallBack(SOCKET_ACCEPT_CALLBACK pAcceptCB) ;
	void SetSocketReporter(CMyDialog *pDialog) ;

	void Close() ;

	BOOL SetTimeOut(DWORD dwTimeOut=MAX_QS_TIMEOUT, DWORD dwFlags=3) ;
	BOOL SetBufferSize(DWORD dwTimeOut=MAX_QS_TIMEOUT, DWORD dwFlags=3) ;
	int Send(void *pszBuf, int dwLen=0, int nTimeOut=15000) ;
	int Recv(void *pszBuf, int dwLen=128, int nTimeOut=15000) ;

private:
	void DoListen() ;
	void DoConnect() ;
	void DoInit();

	BOOL m_bUDP;

	BOOL m_bEndwork;
	int  m_nTimeout ;
	BOOL m_bAsyncRecv;

	SOCKET m_nSock ;
	SOCKET m_dwUDPBuffSize ;
	BYTE  *m_pszUDPDataBuf ;

	WORD  m_nPort ;
	TCHAR  m_szServerIP[64] ;
	SOCKADDR_IN m_UPDRecvAddr ;

	SOCKET_DATAIN_CALLBACK m_pDataInCB ;
	SOCKET_ACCEPT_CALLBACK m_pAcceptCB ;

	CArray<SOCKET,SOCKET>m_arrClients ;

	CMyDialog *m_pReporter ;
};

#endif

