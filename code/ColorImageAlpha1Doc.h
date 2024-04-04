﻿
// ColorImageAlpha1Doc.h: CColorImageAlpha1Doc 클래스의 인터페이스
//


#pragma once


class CColorImageAlpha1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageAlpha1Doc() noexcept;
	DECLARE_DYNCREATE(CColorImageAlpha1Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageAlpha1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	unsigned char** m_outImage = NULL;
	int m_inH = 0 ;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char** OnMalloc2D(int h, int w);
	void OnFree2d(unsigned char** memory, int h);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnFreeOutImage();
	void OnGrayScale();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnAddImage();
	void OnReverseImage();
	void OnBwImage();
	void OnGammaImage();
	void OnBinaryImage();
	void OnCapParaImage();
	void OnCupParaImage();
	void OnZoomOut();
	void OnZoomInForward();
	void OnZoomInBackward();
	void OnChangeSatur();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnPickOrange();
	void OnRotate();
	void OnRotateBackward();
	void OnMove();
	void OnLfMirror();
	void OnUdMirror();
	void OnStretching();
	void OnEndIn();
	void OnEqualizing();
	void OnEmboss();
	double** OnMallocDoubleMemory(int h, int w);
	void OnFreeDoubleMemory(double** memory, int h);
	void OnBlur();
	void OnSharpen();
	void OnEdge1();
	void OnEmbossHsi();
	void OnEdge2();
	void OnEdge3();
	void OnEdge4();
	void OnEdge1Hsi();
	
};
