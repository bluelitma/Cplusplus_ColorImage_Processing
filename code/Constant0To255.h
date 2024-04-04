#pragma once
#include "afxdialogex.h"


// CConstant0To255 대화 상자

class CConstant0To255 : public CDialog
{
	DECLARE_DYNAMIC(CConstant0To255)

public:
	CConstant0To255(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstant0To255();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_0TO255 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constant;
};
