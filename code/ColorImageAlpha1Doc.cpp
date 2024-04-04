
// ColorImageAlpha1Doc.cpp: CColorImageAlpha1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageAlpha1.h"
#endif

#include "ColorImageAlpha1Doc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include "Constant0To100Dlg.h"
#include "Constant0To255.h"
#include "Constant0To4Dlg.h"
#include "Constant0To360Dlg.h"
#include "ConstantAskTwoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageAlpha1Doc

IMPLEMENT_DYNCREATE(CColorImageAlpha1Doc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageAlpha1Doc, CDocument)
END_MESSAGE_MAP()


// CColorImageAlpha1Doc 생성/소멸

CColorImageAlpha1Doc::CColorImageAlpha1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageAlpha1Doc::~CColorImageAlpha1Doc()
{
}

BOOL CColorImageAlpha1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImageAlpha1Doc serialization

void CColorImageAlpha1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageAlpha1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageAlpha1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageAlpha1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageAlpha1Doc 진단

#ifdef _DEBUG
void CColorImageAlpha1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageAlpha1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageAlpha1Doc 명령


BOOL CColorImageAlpha1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// 기존 메모리 해제
	if (m_inImageR != NULL) {
		OnFree2d(m_inImageR, m_inH);
		OnFree2d(m_inImageG, m_inH);
		OnFree2d(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2d(m_outImageR, m_outH);
		OnFree2d(m_outImageG, m_outH);
		OnFree2d(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
	
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 크기 알아내기~
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage의 객체값 --> 메모리
	COLORREF  px;
	for (int i=0; i<m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			px = image.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}

	return TRUE;
}


unsigned char** CColorImageAlpha1Doc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];
	return memory;
}


void CColorImageAlpha1Doc::OnFree2d(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}

double** CColorImageAlpha1Doc::OnMallocDoubleMemory(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;

	retMemory = (double**)malloc(sizeof(double*) * h);
	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);

	return retMemory;
}


void CColorImageAlpha1Doc::OnFreeDoubleMemory(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}

void CColorImageAlpha1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2d(m_inImageR, m_inH);
	OnFree2d(m_inImageG, m_inH);
	OnFree2d(m_inImageB, m_inH);

	OnFree2d(m_outImageR, m_outH);
	OnFree2d(m_outImageG, m_outH);
	OnFree2d(m_outImageB, m_outH);

	CDocument::OnCloseDocument();
}


void CColorImageAlpha1Doc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2d(m_outImageR, m_outH);
		OnFree2d(m_outImageG, m_outH);
		OnFree2d(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
}
void CColorImageAlpha1Doc::OnEqualImage()
{

	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}

}




void CColorImageAlpha1Doc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char) avg;
		}
	}
}


BOOL CColorImageAlpha1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;
	CImage image;
	image.Create(m_outW, m_outH, 32);
	unsigned char R, G, B;
	COLORREF px;
	for(int i=0; i<m_outW; i++) 
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);
	return TRUE;
}


void CColorImageAlpha1Doc::OnAddImage()
{
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageR[i][k] + value > 255)
				m_outImageR[i][k] = 255;
			else if (m_inImageR[i][k] + value < 0)
				m_outImageR[i][k] = 0;
			else
				m_outImageR[i][k] = m_inImageR[i][k] + value;
		}
	}
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageG[i][k] + value > 255)
				m_outImageG[i][k] = 255;
			else if (m_inImageG[i][k] + value < 0)
				m_outImageG[i][k] = 0;
			else
				m_outImageG[i][k] = m_inImageG[i][k] + value;
		}
	}
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImageB[i][k] + value > 255)
				m_outImageB[i][k] = 255;
			else if (m_inImageB[i][k] + value < 0)
				m_outImageB[i][k] = 0;
			else
				m_outImageB[i][k] = m_inImageB[i][k] + value;
		}
	}
}


void CColorImageAlpha1Doc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] > 127)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = 0;
		}
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageG[i][k] > 127)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = 0;
		}
	}
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageB[i][k] > 127)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = 0;
		}
	}
}


void CColorImageAlpha1Doc::OnGammaImage()
{
	CConstant0To100Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	float gamma = dlg.m_constant;

	if (gamma == 1 || gamma == 1.0)
		m_outImageR = m_inImageR;
	else {
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				float m = m_inImageR[i][k];
				m_outImageR[i][k] = (unsigned char)255.0 * pow(m / 255.0, gamma);
			}
		}
	}

	if (gamma == 1 || gamma == 1.0)
		m_outImageG = m_inImageG;
	else {
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				float m = m_inImageG[i][k];
				m_outImageG[i][k] = (unsigned char)255.0 * pow(m / 255.0, gamma);
			}
		}
	}

	if (gamma == 1 || gamma == 1.0)
		m_outImageB = m_inImageB;
	else {
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				float m = m_inImageB[i][k];
				m_outImageB[i][k] = (unsigned char)255.0 * pow(m / 255.0, gamma);
			}
		}
	}

}


void CColorImageAlpha1Doc::OnBinaryImage()
{
	CConstant0To255 dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_inH; i++) { // 이진화 알고리즘
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] > value)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = 0;

		}
	}
	for (int i = 0; i < m_inH; i++) { // 이진화 알고리즘
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageG[i][k] > value)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = 0;

		}
	}
	for (int i = 0; i < m_inH; i++) { // 이진화 알고리즘
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageB[i][k] > value)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = 0;

		}
	}
}


void CColorImageAlpha1Doc::OnCapParaImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)255.0 - 255.0 * pow((m_inImageR[i][k] / 128.0 - 1.0), 2);
			m_outImageG[i][k] = (unsigned char)255.0 - 255.0 * pow((m_inImageG[i][k] / 128.0 - 1.0), 2);
			m_outImageB[i][k] = (unsigned char)255.0 - 255.0 * pow((m_inImageB[i][k] / 128.0 - 1.0), 2);

		}
	}
}


void CColorImageAlpha1Doc::OnCupParaImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)255.0 * pow((m_inImageR[i][k] / 128.0 - 1.0), 2);
			m_outImageG[i][k] = (unsigned char)255.0 * pow((m_inImageG[i][k] / 128.0 - 1.0), 2);
			m_outImageB[i][k] = (unsigned char)255.0 * pow((m_inImageB[i][k] / 128.0 - 1.0), 2);
		}
	}
}


void CColorImageAlpha1Doc::OnZoomOut()
{
	CConstant0To4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int value = (int)dlg.m_constant;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = (m_inH / value);
	m_outW = (m_inW / value);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[(int)(i / value)][(int)(k / value)] = m_inImageR[i][k];
			m_outImageG[(int)(i / value)][(int)(k / value)] = m_inImageG[i][k];
			m_outImageB[(int)(i / value)][(int)(k / value)] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnZoomInForward()
{
	CConstant0To4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int value = (int)dlg.m_constant;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = (m_inH * value);
	m_outW = (m_inW * value);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[(int)(i * value)][(int)(k * value)] = m_inImageR[i][k];
			m_outImageG[(int)(i * value)][(int)(k * value)] = m_inImageG[i][k];
			m_outImageB[(int)(i * value)][(int)(k * value)] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnZoomInBackward()
{
	CConstant0To4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int value = (int)dlg.m_constant;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = (m_inH * value);
	m_outW = (m_inW * value);
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_outH; i++) { // 이진화 알고리즘
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = m_inImageR[(int)(i / value)][(int)(k / value)];
			m_outImageG[i][k] = m_inImageG[(int)(i / value)][(int)(k / value)];
			m_outImageB[i][k] = m_inImageB[(int)(i / value)][(int)(k / value)];

		}
	}
}


void CColorImageAlpha1Doc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) : 0~360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;
			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];	S = hsi[1];	I = hsi[2];

			/// 채도(S) 흐리게
			S = S - 0.2;
			if (S < 0)
				S = 0.0;

			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0]; G = rgb[1]; B = rgb[2];

			m_outImageR[i][k] = R;
			m_outImageG[i][k] = G;
			m_outImageB[i][k] = B;
		}
	}
}


double* CColorImageAlpha1Doc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CColorImageAlpha1Doc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}


void CColorImageAlpha1Doc::OnPickOrange()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HSI 모델 값
			// H(색상) : 0 ~ 360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;

			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];

			/// 오렌지 추출 (H : 8~20)
			if (8 <= H && H <= 30) {
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			else {
				double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
			}
		}
	}
}


void CColorImageAlpha1Doc::OnRotate()
{
	CConstant0To360Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int degree = (int)dlg.m_constant;
	double radian = degree * 3.141592 / 180.0;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
				m_outImageR[xd][yd] = m_inImageR[xs][ys],
				m_outImageG[xd][yd] = m_inImageG[xs][ys],
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
				

		}
	}
}


void CColorImageAlpha1Doc::OnRotateBackward()
{
	CConstant0To360Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int degree = (int)dlg.m_constant;
	double radian = degree * 3.141592 / 180.0;
	int cx = m_inH / 2;
	int cy = m_inW / 2;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int xd = i;
			int yd = k;
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				m_outImageR[xd][yd] = m_inImageR[xs][ys],
				m_outImageG[xd][yd] = m_inImageG[xs][ys],
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
		}
	}
}


void CColorImageAlpha1Doc::OnMove()
{
	CConstantAskTwoDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int D = dlg.m_constant1;
	int R = dlg.m_constant2;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int mv_i = i + D;
			int mv_k = k + R;
			if (0 <= mv_i && mv_i < m_outH && 0 <= mv_k && mv_k < m_outW)
				m_outImageR[mv_i][mv_k] = m_inImageR[i][k],
				m_outImageG[mv_i][mv_k] = m_inImageG[i][k],
				m_outImageB[mv_i][mv_k] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnLfMirror()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][m_outW - k - 1] = m_inImageR[i][k],
			m_outImageG[i][m_outW - k - 1] = m_inImageG[i][k],
			m_outImageB[i][m_outW - k - 1] = m_inImageB[i][k];

		}
	}
}


void CColorImageAlpha1Doc::OnUdMirror()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[m_outH - i - 1][k] = m_inImageR[i][k],
			m_outImageG[m_outH - i - 1][k] = m_inImageG[i][k],
			m_outImageB[m_outH - i - 1][k] = m_inImageB[i][k];
		}
	}
}


void CColorImageAlpha1Doc::OnStretching()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int highR = m_inImageR[0][0];
	int lowR = m_inImageR[0][0];

	int highG = m_inImageG[0][0];
	int lowG = m_inImageG[0][0];

	int highB = m_inImageB[0][0];
	int lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k];
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];

			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k];
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];

			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k];
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int oldthingR = m_inImageR[i][k];
			int newthingR = (int)((double)(oldthingR - lowR) / (double)(highR - lowR) * 255.0);

			int oldthingG = m_inImageG[i][k];
			int newthingG = (int)((double)(oldthingG - lowG) / (double)(highG - lowG) * 255.0);

			int oldthingB = m_inImageB[i][k];
			int newthingB = (int)((double)(oldthingB - lowB) / (double)(highB - lowB) * 255.0);

			if (newthingR > 255)
				newthingR = 255;
			if (newthingR < 0)
				newthingR = 0;
			m_outImageR[i][k] = newthingR;

			if (newthingG > 255)
				newthingG = 255;
			if (newthingG < 0)
				newthingG = 0;
			m_outImageG[i][k] = newthingG;

			if (newthingB > 255)
				newthingB = 255;
			if (newthingB < 0)
				newthingB = 0;
			m_outImageB[i][k] = newthingB;
		}
	}
}


void CColorImageAlpha1Doc::OnEndIn()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int highR = m_inImageR[0][0];
	int lowR = m_inImageR[0][0];

	int highG = m_inImageG[0][0];
	int lowG = m_inImageG[0][0];

	int highB = m_inImageB[0][0];
	int lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < lowR)
				lowR = m_inImageR[i][k];
			if (m_inImageR[i][k] > highR)
				highR = m_inImageR[i][k];

			if (m_inImageG[i][k] < lowG)
				lowG = m_inImageG[i][k];
			if (m_inImageG[i][k] > highG)
				highG = m_inImageG[i][k];

			if (m_inImageB[i][k] < lowB)
				lowB = m_inImageB[i][k];
			if (m_inImageB[i][k] > highB)
				highB = m_inImageB[i][k];
		}
	}

	highR -= 50, highG -= 50, highB -= 50;
	lowR += 50, lowG += 50, lowB += 50;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int oldthingR = m_inImageR[i][k];
			int newthingR = (int)((double)(oldthingR - lowR) / (double)(highR - lowR) * 255.0);

			int oldthingG = m_inImageG[i][k];
			int newthingG = (int)((double)(oldthingG - lowG) / (double)(highG - lowG) * 255.0);

			int oldthingB = m_inImageB[i][k];
			int newthingB = (int)((double)(oldthingB - lowB) / (double)(highB - lowB) * 255.0);

			if (newthingR > 255)
				newthingR = 255;
			if (newthingR < 0)
				newthingR = 0;
			m_outImageR[i][k] = newthingR;

			if (newthingG > 255)
				newthingG = 255;
			if (newthingG < 0)
				newthingG = 0;
			m_outImageG[i][k] = newthingG;

			if (newthingB > 255)
				newthingB = 255;
			if (newthingB < 0)
				newthingB = 0;
			m_outImageB[i][k] = newthingB;
		}
	}
}


void CColorImageAlpha1Doc::OnEqualizing()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 1단계 : 빈도수 세기(=히스토그램) histo[256]
	int histoR[256] = { 0, };
	int histoG[256] = { 0, };
	int histoB[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	// 2단계 : 누적 히스토그램 생성
	int sumHistoR[256] = { 0, };
	sumHistoR[0] = histoR[0];

	int sumHistoG[256] = { 0, };
	sumHistoG[0] = histoG[0];

	int sumHistoB[256] = { 0, };
	sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++) {
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];
	}

	// 3단계 : 정규화 된 히스토그램 생성 normalHisto = sumHisto * ( 1 / (inH*inW) ) * 255.0
	double normalHistoR[256] = { 1.0, };
	double normalHistoG[256] = { 1.0, };
	double normalHistoB[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)normalHistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = (unsigned char)normalHistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = (unsigned char)normalHistoB[m_inImageB[i][k]];
		}
	}
}


void CColorImageAlpha1Doc::OnEmboss()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[3][3] = { // 마스크
		{-1.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 1.0}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], 
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], 
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	// 후처리 (마스크 값의 합계에 따라서 ...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEmbossHsi()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[3][3] = { // 마스크
		{-1.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 1.0}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageH, ** tmpInImageS, ** tmpInImageI;
	tmpInImageH = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInImageG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];
		}
	///////// RGB 모델 --> HSI모델 ///////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k];
			G = tmpInImageG[i][k];
			B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	// *** 회선 연산 : 마스크로 긁어가면서 계산하기
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE;
			S_VALUE = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서 ...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpInImageI[i][k] += 127;

	//////// HSI --> RGB //////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];

		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);

	OnFreeDoubleMemory(tmpInImageH, m_inH + 2);
	OnFreeDoubleMemory(tmpInImageS, m_inH + 2);
	OnFreeDoubleMemory(tmpInImageI, m_inH + 2);
}


void CColorImageAlpha1Doc::OnBlur()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[3][3] = { // 마스크
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	//// 후처리 (마스크 값의 합계에 따라서 ...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnSharpen()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[3][3] = { // 마스크
		{-1.0, -1.0, -1.0},
		{-1.0,  9.0, -1.0},
		{-1.0, -1.0, -1.0}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	//// 후처리 (마스크 값의 합계에 따라서 ...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge1()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[3][3] = { // 마스크
		{ 0.0, 0.0, 0.0},
		{-1.0, 1.0, 0.0},
		{ 0.0, 0.0, 0.0}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	//// 후처리 (마스크 값의 합계에 따라서 ...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}





void CColorImageAlpha1Doc::OnEdge2()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[3][3] = { // 마스크
		{ 1.0, 1.0, 1.0},
		{ 1.0,-8.0, 1.0},
		{ 1.0, 1.0, 1.0}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	//// 후처리 (마스크 값의 합계에 따라서 ...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 2);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge3()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[5][5] = { // 마스크
		{ 0.0, 0.0,-1.0, 0.0, 0.0 },
		{ 0.0,-1.0,-2.0,-1.0, 0.0 },
		{-1.0,-2.0,16.0,-2.0,-1.0 },
		{ 0.0,-1.0,-2.0,-1.0, 0.0 },
		{ 0.0, 0.0,-1.0, 0.0, 0.0 }
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 4, m_inW + 4);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 4, m_inW + 4);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 4, m_inW + 4);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 4; i++)
		for (int k = 0; k < m_inW + 4; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	//// 후처리 (마스크 값의 합계에 따라서 ...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 4);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 4);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 4);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge4()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 엠보싱 이미지 영상 처리 <핵심 알고리즘>
	//////////////////////
	// 화소 영역 처리
	//////////////////////
	double mask[7][7] = { // 마스크
		{ 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0},
		{ 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
		{-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
		{-1.0,-3.0, 5.0,16.0, 5.0,-3.0,-1.0},
		{-1.0,-3.0, 5.0, 5.0, 5.0,-3.0,-1.0},
		{ 0.0,-2.0,-3.0,-3.0,-3.0,-2.0, 0.0},
		{ 0.0, 0.0,-1.0,-1.0,-1.0, 0.0, 0.0}
	};

	////////////////////////////////////////////////////////////////////////////////
	//임시 메모리 할당(실수형)
	double** tmpInImageR = OnMallocDoubleMemory(m_inH + 6, m_inW + 6);
	double** tmpOutImageR = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageG = OnMallocDoubleMemory(m_inH + 6, m_inW + 6);
	double** tmpOutImageG = OnMallocDoubleMemory(m_outH, m_outW);

	double** tmpInImageB = OnMallocDoubleMemory(m_inH + 6, m_inW + 6);
	double** tmpOutImageB = OnMallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 6; i++)
		for (int k = 0; k < m_inW + 6; k++)
			tmpInImageR[i][k] = 127, tmpInImageG[i][k] = 127, tmpInImageB[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImageR[i + 1][k + 1] = m_inImageR[i][k], tmpInImageG[i + 1][k + 1] = m_inImageG[i][k], tmpInImageB[i + 1][k + 1] = m_inImageB[i][k];

	// ***회선 연산***
	double S_R;
	double S_G;
	double S_B;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크와 한점을 중심으로한 3x3을 곱하기
			S_R = S_G = S_B = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S_R += tmpInImageR[i + m][k + n] * mask[m][n],
					S_G += tmpInImageG[i + m][k + n] * mask[m][n],
					S_B += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S_R, tmpOutImageG[i][k] = S_G, tmpOutImageB[i][k] = S_B;

		}
	}
	//// 후처리 (마스크 값의 합계에 따라서 ...)
	//for (int i = 0; i < m_outH; i++)
	//	for (int k = 0; k < m_outW; k++)
	//		tmpOutImageR[i][k] += 127.0, tmpOutImageG[i][k] += 127.0, tmpOutImageB[i][k] += 127.0;

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}

	OnFreeDoubleMemory(tmpInImageR, m_inH + 6);
	OnFreeDoubleMemory(tmpOutImageR, m_outH);

	OnFreeDoubleMemory(tmpInImageG, m_inH + 6);
	OnFreeDoubleMemory(tmpOutImageG, m_outH);

	OnFreeDoubleMemory(tmpInImageB, m_inH + 6);
	OnFreeDoubleMemory(tmpOutImageB, m_outH);
}


void CColorImageAlpha1Doc::OnEdge1Hsi()
{
	// TODO: 여기에 구현 코드 추가.
	
}
