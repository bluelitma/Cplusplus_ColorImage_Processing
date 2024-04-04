// ConstantAskTwoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "ConstantAskTwoDlg.h"


// CConstantAskTwoDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantAskTwoDlg, CDialog)

CConstantAskTwoDlg::CConstantAskTwoDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_ASKTWO, pParent)
	, m_constant1(0)
	, m_constant2(0)
{

}

CConstantAskTwoDlg::~CConstantAskTwoDlg()
{
}

void CConstantAskTwoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant1);
	DDV_MinMaxInt(pDX, m_constant1, -255, 255);
	DDX_Text(pDX, IDC_EDIT_CONSTANT2, m_constant2);
	DDV_MinMaxInt(pDX, m_constant2, -255, 255);
}


BEGIN_MESSAGE_MAP(CConstantAskTwoDlg, CDialog)
END_MESSAGE_MAP()


// CConstantAskTwoDlg 메시지 처리기
