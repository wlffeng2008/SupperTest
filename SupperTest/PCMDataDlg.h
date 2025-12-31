#pragma once
#include "afxdialogex.h"


// CPCMDataDlg dialog

class CPCMDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPCMDataDlg)

public:
	CPCMDataDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPCMDataDlg();

	float m_data[1920];
	void DrawCurv(const float* data, int nCount = 480);

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
