#pragma once
#include "afxdialogex.h"


// CConstant0To100Dlg 대화 상자

class CConstant0To100Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant0To100Dlg)

public:
	CConstant0To100Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstant0To100Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_0TO100 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_constant;
};
