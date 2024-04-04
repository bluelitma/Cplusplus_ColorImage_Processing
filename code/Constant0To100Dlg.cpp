// Constant0To100Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant0To100Dlg.h"


// CConstant0To100Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant0To100Dlg, CDialog)

CConstant0To100Dlg::CConstant0To100Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_0TO100, pParent)
	, m_constant(0)
{

}

CConstant0To100Dlg::~CConstant0To100Dlg()
{
}

void CConstant0To100Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxFloat(pDX, m_constant, 0, 100);
}


BEGIN_MESSAGE_MAP(CConstant0To100Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant0To100Dlg 메시지 처리기
