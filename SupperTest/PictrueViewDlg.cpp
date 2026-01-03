// PictrueViewDlg.cpp : implementation file
//

#include "pch.h"
#include "SupperTest.h"
#include "afxdialogex.h"
#include "PictrueViewDlg.h"


// CPictrueViewDlg dialog

IMPLEMENT_DYNAMIC(CPictrueViewDlg, CDialogEx)

CPictrueViewDlg::CPictrueViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PICVIEW_DIALOG, pParent)
{

}

CPictrueViewDlg::~CPictrueViewDlg()
{
}

void CPictrueViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CPictrueViewDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CSvgRenderer::CSvgRenderer()
	: m_pSvgImage(nullptr), m_pRasterizer(nullptr)
{
	m_pRasterizer = nsvgCreateRasterizer(); // 创建光栅化器
}

CSvgRenderer::~CSvgRenderer()
{
	if (m_pSvgImage)   nsvgDelete(m_pSvgImage);
	if (m_pRasterizer) nsvgDeleteRasterizer(m_pRasterizer);
}

BOOL CSvgRenderer::Render(LPCTSTR szSvgPath, CDC* pDC, const CRect& rcDst, BOOL bReload)
{
	if (m_pSvgImage && (bReload || m_strFile != szSvgPath))
	{
		nsvgDelete(m_pSvgImage);
		m_pSvgImage = nullptr;
	}
	if (!m_pSvgImage)
	{
		LoadSvg(szSvgPath);
		m_strFile = szSvgPath;
	}

	return Render(pDC, rcDst);
}

BOOL CSvgRenderer::LoadSvg(LPCTSTR szSvgPath)
{
	if (!wcswcs(szSvgPath, _T(".svg")))
		return FALSE;
	// 解析SVG（第二个参数为单位："px"|"pt"|"em"|"%"，默认px）
	m_pSvgImage = nsvgParseFromFile(UTF8Encode(CW2A(szSvgPath)), "px", 96.0f);
	if (!m_pSvgImage)
		m_pSvgImage = nsvgParse(CW2A(szSvgPath), "px", 96.0f);

	if (m_pSvgImage)
	{
		if (m_pSvgImage->width == 0 || m_pSvgImage->height == 0)
		{
			nsvgDelete(m_pSvgImage);
			m_pSvgImage = nullptr;
		}
	}

	return (m_pSvgImage != nullptr);
}

BOOL CSvgRenderer::Render(CDC* pDC, const CRect& rcDst)
{
	if (!m_pSvgImage || !m_pRasterizer || !pDC)
		return FALSE;

	float fSvgWidth = m_pSvgImage->width;
	float fSvgHeight = m_pSvgImage->height;

	float fScaleX = (float)rcDst.Width() / fSvgWidth;
	float fScaleY = (float)rcDst.Height() / fSvgHeight;
	float fScale = min(fScaleX, fScaleY); // 等比缩放

	int nRenderWidth = (int)(fSvgWidth * fScale);
	int nRenderHeight = (int)(fSvgHeight * fScale);
	int nOffsetX = rcDst.left + (rcDst.Width() - nRenderWidth) / 2;
	int nOffsetY = rcDst.top + (rcDst.Height() - nRenderHeight) / 2;

	unsigned char* pPixels = new unsigned char[nRenderWidth * nRenderHeight * 4];
	nsvgRasterize(m_pRasterizer, m_pSvgImage, 0, 0, fScale, pPixels, nRenderWidth, nRenderHeight, nRenderWidth * 4);

	for (int y = 0; y < nRenderHeight; y++)
	{
		for (int x = 0; x < nRenderWidth; x++)
		{
			int idx = (y * nRenderWidth + x) * 4;
			unsigned char R = pPixels[idx + 0];
			unsigned char B = pPixels[idx + 2];
			pPixels[idx] = B;
			pPixels[idx + 2] = R;
		}
	}

	Bitmap bitmap(nRenderWidth, nRenderHeight, nRenderWidth * 4, PixelFormat32bppARGB, pPixels);
	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
	//graphics.DrawImage(&bitmap, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height());
	graphics.DrawImage(&bitmap, nOffsetX, nOffsetY, nRenderWidth, nRenderHeight);

	graphics.DrawImage(&bitmap, rcDst.left + 5, rcDst.top + 5, (INT)(100.0 * fSvgWidth / fSvgHeight), 100);

	delete[] pPixels;
	return TRUE;
}


// 正确的WIC加载WebP函数（修复Lock调用错误）
Bitmap* LoadWebPByWIC(LPCTSTR szWebPPath)
{
	if (!wcswcs(szWebPPath, _T(".webp")))
		return FALSE;
	// 1. 初始化COM（确保线程COM已初始化，MFC中AfxOleInit()已处理，此处兜底）
	static HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	IWICImagingFactory* pWICFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	IWICBitmap* pWICBitmap = nullptr;
	IWICBitmapLock* pLock = nullptr;
	static Bitmap* pGdiBitmap = nullptr;

	if (pGdiBitmap)
		delete pGdiBitmap;

	do {
		hr = CoCreateInstance(
			CLSID_WICImagingFactory2,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pWICFactory)
		);
		if (FAILED(hr)) {
			AfxMessageBox(_T("创建WIC工厂失败！"));
			break;
		}

		// 3. 创建WebP解码器
		hr = pWICFactory->CreateDecoderFromFilename(
			szWebPPath,
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
		if (FAILED(hr)) {
			AfxMessageBox(_T("创建WebP解码器失败（系统可能不支持WebP）！"));
			break;
		}

		// 4. 获取第一帧
		hr = pDecoder->GetFrame(0, &pFrame);
		if (FAILED(hr)) {
			AfxMessageBox(_T("获取WebP帧失败！"));
			break;
		}

		// 5. 创建格式转换器（转为GDI+兼容的BGRA格式）
		hr = pWICFactory->CreateFormatConverter(&pConverter);
		if (FAILED(hr)) break;

		hr = pConverter->Initialize(
			pFrame,
			GUID_WICPixelFormat32bppBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
		if (FAILED(hr)) {
			AfxMessageBox(_T("格式转换初始化失败！"));
			break;
		}

		// 6. 关键修复：将转换后的帧转为IWICBitmap，再调用Lock
		hr = pWICFactory->CreateBitmapFromSource(
			pConverter,
			WICBitmapCacheOnDemand,
			&pWICBitmap
		);
		if (FAILED(hr)) break;

		// 7. 获取图像尺寸
		UINT nWidth = 0;
		UINT nHeight = 0;
		hr = pWICBitmap->GetSize(&nWidth, &nHeight);
		if (FAILED(hr)) break;

		// 8. 锁定WIC位图内存（此时调用的是IWICBitmap的Lock，而非Converter）
		WICRect rect = { 0, 0, (int)nWidth, (int)nHeight };
		hr = pWICBitmap->Lock(&rect, WICBitmapLockRead, &pLock);
		if (FAILED(hr)) {
			AfxMessageBox(_T("锁定WIC位图内存失败！"));
			break;
		}

		// 9. 获取像素数据并创建GDI+ Bitmap
		UINT nStride = 0;
		BYTE* pPixels = nullptr;
		UINT nBufferSize = 0;
		hr = pLock->GetStride(&nStride);
		hr |= pLock->GetDataPointer(&nBufferSize, &pPixels);
		if (FAILED(hr)) break;

		// 创建GDI+位图（BGRA格式与WIC转换结果匹配）
		pGdiBitmap = new Bitmap(nWidth, nHeight, nStride, PixelFormat32bppARGB, pPixels);
		if (pGdiBitmap->GetLastStatus() != Ok)
		{
			delete pGdiBitmap;
			pGdiBitmap = nullptr;
		}

	} while (false);

	// 10. 释放所有WIC资源（按逆序释放）

	//if (pLock) pLock->Release();
	if (pWICBitmap) pWICBitmap->Release();
	if (pConverter) pConverter->Release();
	if (pFrame) pFrame->Release();
	if (pDecoder) pDecoder->Release();
	if (pWICFactory) pWICFactory->Release();

	return pGdiBitmap;
}

// 加载AVIF并转换为GDI+ Bitmap
Bitmap* LoadAVIFByLibAVIF(LPCTSTR szAVIFPath)
{
	return nullptr;
#if 0
	avifDecoder* pDecoder = avifDecoderCreate();
	avifResult res = avifDecoderSetIOFile(pDecoder, UTF8Encode(CW2A(szAVIFPath)));
	if (res != AVIF_RESULT_OK) {
		avifDecoderDestroy(pDecoder);
		return nullptr;
	}
	res = avifDecoderParse(pDecoder);
	if (res != AVIF_RESULT_OK) {
		avifDecoderDestroy(pDecoder);
		return nullptr;
	}
	res = avifDecoderNextImage(pDecoder);
	if (res != AVIF_RESULT_OK) {
		avifDecoderDestroy(pDecoder);
		return nullptr;
	}

	// 3. 获取解码后的RGBA像素数据
	avifImage* pImage = pDecoder->image;
	int nWidth = pImage->width;
	int nHeight = pImage->height;
	// 将YUV转换为RGBA（avif内置转换函数）
	avifRGBImage rgbImage;
	avifRGBImageSetDefaults(&rgbImage, pImage);
	rgbImage.format = AVIF_RGB_FORMAT_BGRA; // 适配GDI+的BGRA格式
	rgbImage.depth = 8;
	avifRGBImageAllocatePixels(&rgbImage);
	avifImageYUVToRGB(pImage, &rgbImage);

	// 4. 创建GDI+ Bitmap
	Bitmap* pBitmap = new Bitmap(nWidth, nHeight, nWidth * 4, PixelFormat32bppARGB, rgbImage.pixels);

	// 5. 释放资源
	avifRGBImageFreePixels(&rgbImage);
	avifDecoderDestroy(pDecoder);

	return (pBitmap->GetLastStatus() == Ok) ? pBitmap : nullptr;
#endif
}


BOOL CPictrueViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	SetDlgBKColor(RGB(240, 240, 255));

	m_strSvgFile = ::GetCurrentPath() + _T("\\images\\reliable.svg");
	//AddFillRect(0, 0, -1, -1, 1, RGB(255,0,0),1,);
	return TRUE;
}

BOOL CPictrueViewDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case CMD_DROPFILES_NOTIFY:
	{
		HDROP hDrop = (HDROP)lParam;
		UINT nFileCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
		TCHAR szFilePath[MAX_PATH] = { 0 };
		for (UINT i = 0; i < nFileCount; i++)
		{
			if (DragQueryFile(hDrop, i, szFilePath, MAX_PATH))
			{
				m_strSvgFile = szFilePath;
				RedrawWindow();
				break;
			}
		}
		break;
	}

	}

	return CDialogEx::OnCommand(wParam, lParam);
}


void CPictrueViewDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);
	DrawDialog(&dc);
	rc.top += 20;
	if (!m_svgRenderer.Render(m_strSvgFile, &dc, rc))
	{
		Bitmap* pBM = LoadWebPByWIC(m_strSvgFile);
		if (!pBM) pBM = LoadAVIFByLibAVIF(m_strSvgFile);
		if (!pBM) pBM = Bitmap::FromFile(m_strSvgFile);

		if (pBM)
		{
			int fSvgWidth = pBM->GetWidth();
			int fSvgHeight = pBM->GetHeight();
			Graphics graphics(dc.GetSafeHdc());
			graphics.DrawImage(pBM, rc.left, rc.top, rc.Width(), rc.Height());
			graphics.DrawImage(pBM, rc.left + 5, rc.top + 5, (INT)(100.0 * fSvgWidth / fSvgHeight), 100);
		}
		else
		{
			dc.TextOut(10, 10, _T("SVG加载失败！"));
		}
	}
}

