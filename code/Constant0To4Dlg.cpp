// Constant0To4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant0To4Dlg.h"


// CConstant0To4Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant0To4Dlg, CDialog)

CConstant0To4Dlg::CConstant0To4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_0TO4, pParent)
	, m_constant(0)
{

}

CConstant0To4Dlg::~CConstant0To4Dlg()
{
}

void CConstant0To4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxDouble(pDX, m_constant, 0, 10);
}


BEGIN_MESSAGE_MAP(CConstant0To4Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant0To4Dlg 메시지 처리기
