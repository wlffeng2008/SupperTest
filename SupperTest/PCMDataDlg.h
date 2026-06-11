#pragma once
#include "afxdialogex.h"


// CPCMDataDlg dialog
typedef struct 
{
	BYTE* data;
	int len;
}PCMData;

class CPCMDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPCMDataDlg)

public:
	CPCMDataDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPCMDataDlg();

	float m_data[1920];
	void DrawCurv(const float* data, int nCount = 480);

	CList<PCMData*> m_lstData;
	int OnSimpleThreadLoopRun(int nWorkerID);

	void StartRecord();
	void StopRecord();
	CString m_strFile;
	CFile m_RecFile;
	BOOL m_bRecording = false;
	DWORD m_dwWrite = 0;
	DWORD m_dwDuration = 0;
	DWORD m_dwStartTick = 0;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PCMVIEW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};
