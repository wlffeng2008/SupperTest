// DirDialog.h

#if !defined(AFX_DIRDIALOG_H__62FFAC92_1DEE_11D1_B87A_0060979CDF6D__INCLUDED_)
#define AFX_DIRDIALOG_H__62FFAC92_1DEE_11D1_B87A_0060979CDF6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDirDialog
{
public:
	CDirDialog();
	virtual ~CDirDialog();
	int DoBrowse(CWnd *pwndParent);

	CString m_strPath;
	CString m_strFixDir;
	CString m_strSelDir;
	CString m_strWindowTitle;
	int     m_nImageIndex;
};

#endif


