// PCMDataDlg.cpp : implementation file
//

#include "pch.h"
#include "SupperTest.h"
#include "afxdialogex.h"
#include "PCMDataDlg.h"


// CPCMDataDlg dialog

static CPCMDataDlg *pWDlg = nullptr;

IMPLEMENT_DYNAMIC(CPCMDataDlg, CDialogEx)

CPCMDataDlg::CPCMDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PCMVIEW_DIALOG, pParent)
{
	pWDlg = this;
}

CPCMDataDlg::~CPCMDataDlg()
{
}

void CPCMDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPCMDataDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CPCMDataDlg::DrawCurv(const float* data, int nCount)
{
	for (int i = 0; i < 960; i++)
	{
		m_data[i] = data[i];
	}
	RedrawWindow();
}

void CPCMDataDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(rc);
	int nW = rc.Width();
	int nH = rc.Height();

	Gdiplus::Bitmap bmp(nW, nH, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(&bmp);
	graphics.Clear(Color(255, 255, 255, 255));
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	SolidBrush br(Color::Aqua);
	graphics.FillRectangle(&br, Rect(0, nH / 2 - 200, nW, 400));

	Pen pen1(Color(255, 0, 0), 1);
	Pen pen2(Color(0, 0, 255), 1);
	float xStep = nW * 1.0 / 480;
	int x0 = 0;
	int y0 = m_data[0] * 200 + nH / 2;
	int y2 = m_data[1] * 200 + nH / 2;

	for (int i = 1; i < 960; i += 2)
	{
		int x1 = i * xStep;
		int y1 = m_data[i + 0] * 200 + nH / 2;
		int y3 = m_data[i + 1] * 200 + nH / 2;
		graphics.DrawLine(&pen1, x0, y0, x1, y1);
		graphics.DrawLine(&pen2, x0, y2, x1, y3);

		x0 = x1;
		y0 = y1;
		y2 = y3;
	}

	Pen pen(Color(0, 255, 0), 2);
	graphics.DrawLine(&pen, 0, nH / 2, nW, nH / 2);

	Gdiplus::Graphics Out(dc.GetSafeHdc());
	//Out.Clear(Color(255, 255, 255));
	Out.DrawImage(&bmp, 0, 0);
}

#define  MINIAUDIO_IMPLEMENTATION
#include "../OtherLib/miniaudio.h"

// 音频数据回调函数：每次获取到音频数据时触发
static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
	// pInput 即为捕获到的系统音频数据（格式：pcm_f32，双通道，48000Hz 默认）
	//const float* pcmData = (const float*)pInput;
	//ma_uint32 sampleCount = frameCount * pDevice->capture.format.channels;

	// 1. 此处可将 pcmData 写入缓冲区，供后续语音识别使用
	// 2. 或直接调用语音识别 SDK 的流式接口

	//(void)pOutput; // 未使用输出

	const float* pcmDataO = (const float*)pInput;
	ma_uint32 dataSize = frameCount * pDevice->playback.channels * sizeof(float);
	TRACE(_T("--------%s %d,%d,%d,%d,%d,%d,%d,%d,%d\n"), CA2W((pDevice->playback.name)), dataSize, (int)(pcmDataO[2] * 6), (int)(pcmDataO[25] * 6), (int)(pcmDataO[49] * 6), (int)(pcmDataO[83] * 6),
		(int)(pcmDataO[360] * 6), (int)(pcmDataO[400] * 6), (int)(pcmDataO[430] * 6), (int)(pcmDataO[470] * 6));
	if (pWDlg) pWDlg->DrawCurv(pcmDataO);
}

// CSubDlgWorkinfo message handlers
BOOL CPCMDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 250, 0));
	/*
	static ma_device_config config = ma_device_config_init(ma_device_type_playback);
	config.capture.format = ma_format_f32;    // 采样格式：32位浮点
	config.capture.channels = 2;                // 声道数：立体声
	config.sampleRate = 48000;            // 采样率：48kHz
	config.dataCallback = data_callback;    // 数据回调
	config.pUserData = NULL;

	// 关键：选择系统 "立体声混音" 或 "扬声器" 作为捕获设备
	// 可通过 ma_device_get_list 获取设备列表，选择对应设备 ID
	static ma_device device;
	if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
		return -1;
	}

	// 启动捕获
	if (ma_device_start(&device) != MA_SUCCESS) {
		ma_device_uninit(&device);
	}*/ 
	static ma_device_config config = ma_device_config_init(ma_device_type_loopback);
	config.playback.format = ma_format_f32;
	config.playback.channels = 2;         // 声道数：立体声
	config.sampleRate = 48000;            // Set to 0 to use the device's native sample rate.
	config.dataCallback = data_callback;  // This function will be called when miniaudio needs more data.
	config.pUserData = this;   // Can be accessed from the device object (device.pUserData).
	//config.capture.channels;

	static ma_device device;
	if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {

		OutputDebugString(_T("ERROR --------"));
	}

	ma_device_start(&device);     // The device is sleeping by default so you'll need to start it manually.

	return TRUE;
}