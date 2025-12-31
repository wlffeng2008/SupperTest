#pragma once
#include "afxdialogex.h"


// CPictrueViewDlg dialog

class CSvgRenderer
{
public:
	CSvgRenderer();
	~CSvgRenderer();

	BOOL LoadSvg(LPCTSTR szSvgPath);
	BOOL Render(CDC* pDC, const CRect& rcDst);
	BOOL Render(LPCTSTR szSvgPath, CDC* pDC, const CRect& rcDst, BOOL bReload = FALSE);

private:
	NSVGimage* m_pSvgImage;       // nanosvg 解析后的SVG数据
	NSVGrasterizer* m_pRasterizer;// nanosvg 光栅化器
	CString m_strFile;
};

Bitmap* LoadWebPByWIC(LPCTSTR szWebPPath);
Bitmap* LoadAVIFByLibAVIF(LPCTSTR szAVIFPath);

class CPictrueViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPictrueViewDlg)

public:
	CPictrueViewDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPictrueViewDlg();

	CSvgRenderer m_svgRenderer; // SVG渲染器
	CString m_strSvgFile;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICVIEW_DIALOG };
#endif

protected:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
