
// SupperTestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SupperTest.h"
#include "SupperTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSupperTestDlg dialog



CSupperTestDlg::CSupperTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUPPERTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSupperTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSupperTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSupperTestDlg message handlers

BOOL CSupperTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	m_pPCMDataDlg = new CPCMDataDlg();
	m_pPCMDataDlg->Create(this);
	m_pPictureDlg = new CPictrueViewDlg();
	m_pPictureDlg->Create(this);
	SetDlgItemPos2(m_pPCMDataDlg, IDC_STATIC_FRAME);
	SetDlgItemPos2(m_pPictureDlg, IDC_STATIC_FRAME);

	m_pPCMDataDlg->Show();

	SetSpecialID(-1, IDC_CHECK_ONTOP);

	RAWINPUTDEVICE rid[1];
	rid[0].usUsagePage = 0x01;  // 通用桌面设备 (Generic Desktop Controls)
	rid[0].usUsage = 0x02;      // 鼠标设备 (Mouse)
	rid[0].dwFlags = RIDEV_INPUTSINK; // 允许在窗口失去焦点时也能接收数据
	rid[0].hwndTarget = m_hWnd;   // 接收消息的窗口句柄

	if (!RegisterRawInputDevices(rid, 1, sizeof(rid))) {
		// 注册失败处理
		MessageBox(L"注册原始输入设备失败！", L"错误", MB_OK);
		return FALSE;
	}

	QSetTimer(2, 300);
	return TRUE; 
}

void CSupperTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSupperTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSupperTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CSupperTestDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case IDC_CHECK_SWITCH:
		{
			BOOL bShow = IsDlgButtonChecked(IDC_CHECK_SWITCH);
			m_pPCMDataDlg->Show(!bShow);
			m_pPictureDlg->Show(bShow);
		}
		break;

		case IDC_CHECK_RECORD:
		{
			BOOL bRecord = IsDlgButtonChecked(IDC_CHECK_RECORD);
			KillTimer(1);
			if (bRecord)
			{
				m_pPCMDataDlg->StartRecord();
				QSetTimer(1, 1000);
			}
			else
			{
				m_pPCMDataDlg->StopRecord();
			}
		}
		break;
	default:
		break;
	}
	return CDialogEx::OnCommand(wParam, lParam);	
}


#include <vector>
#include <numeric> // 用于 std::accumulate


class PollingRateCalculator {
private:
	LARGE_INTEGER m_frequency; // 高精度计时器频率
	LARGE_INTEGER m_startTime; // 当前时间窗口的起始时间
	int m_packetCount;         // 当前窗口内收到的数据包数量
	double m_currentPollingRate; // 计算出的回报率 (Hz)
	double m_windowDurationMs; // 时间窗口长度（毫秒），通常设为 1000ms

public:
	PollingRateCalculator(double windowMs = 1000.0)
		: m_packetCount(0), m_currentPollingRate(0.0), m_windowDurationMs(windowMs)
	{
		QueryPerformanceFrequency(&m_frequency);
		QueryPerformanceCounter(&m_startTime);
	}

	// 核心方法：每次收到 Raw Input 时调用
	void ProcessMousePacket() {
		m_packetCount++;

		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		// 计算距离窗口开始经过的时间（毫秒）
		double elapsedMs = (double)(currentTime.QuadPart - m_startTime.QuadPart) * 1000.0 / m_frequency.QuadPart;

		// 如果经过的时间达到了设定的窗口（例如1000ms），则计算回报率并重置
		if (elapsedMs >= m_windowDurationMs) {
			// 回报率 = 总包数 / 实际经过的秒数
			m_currentPollingRate = (double)m_packetCount / (elapsedMs / 1000.0);

			// 重置计数器，开始下一个窗口
			m_packetCount = 0;
			m_startTime = currentTime;
		}
	}

	// 获取当前计算出的回报率
	double GetPollingRate() const {
		return m_currentPollingRate;
	}
};

// 全局或类成员变量
PollingRateCalculator g_pollingCalc(1000.0); // 1000毫秒为一个计算周期
LRESULT CSupperTestDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INPUT:
		{
			UINT dwSize = 0;
			// 1. 获取所需缓冲区大小
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

			// 2. 分配缓冲区并获取实际数据
			LPBYTE lpb = new BYTE[dwSize];
			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
				delete[] lpb;
				break;
			}

			RAWINPUT* raw = (RAWINPUT*)lpb;

			// 3. 确认是鼠标输入
			if (raw->header.dwType == RIM_TYPEMOUSE) {
				RAWMOUSE& mouse = raw->data.mouse;

				// 获取相对移动距离 (lLastX, lLastY)
				int relativeX = mouse.lLastX;
				int relativeY = mouse.lLastY;

				// 【核心逻辑】在此处记录高精度时间戳 (如 QueryPerformanceCounter)
				// 通过统计单位时间（如1秒）内接收到的有效数据包数量，即可得出回报率(Hz)
				// ProcessRawMouseData(relativeX, relativeY);
				g_pollingCalc.ProcessMousePacket();
			}

			delete[] lpb;
		}
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}



void CSupperTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString strInfo;
		DWORD dwDur = m_pPCMDataDlg->m_dwDuration;
		CString strDur;
		strDur.Format(_T("%02d:%02d:%02d"), dwDur / 3600, (dwDur % 3600) / 60, dwDur % 60);
		strInfo.Format(_T("%s [%.2f KB] [%s]"), m_pPCMDataDlg->m_strFile, m_pPCMDataDlg->m_dwWrite / 1024.0, strDur);
		SetDlgItemText(IDC_STATIC_INFO, strInfo);
	}

	if (nIDEvent == 2)
	{
		CString strInfo;
		double rate = g_pollingCalc.GetPollingRate();
		strInfo.Format(_T("Polling Rate: %.2f"), rate);
		SetDlgItemText(IDC_STATIC_RATE, strInfo);
	}
	//CDialogEx::OnTimer(nIDEvent);
}