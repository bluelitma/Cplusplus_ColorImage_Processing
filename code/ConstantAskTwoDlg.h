#pragma once
#include "afxdialogex.h"


// CConstantAskTwoDlg 대화 상자

class CConstantAskTwoDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantAskTwoDlg)

public:
	CConstantAskTwoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantAskTwoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_ASKTWO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constant1;
	int m_constant2;
};
