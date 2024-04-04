// Constant0To360Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant0To360Dlg.h"


// CConstant0To360Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant0To360Dlg, CDialog)

CConstant0To360Dlg::CConstant0To360Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_0TO360, pParent)
	, m_constant(0)
{

}

CConstant0To360Dlg::~CConstant0To360Dlg()
{
}

void CConstant0To360Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxDouble(pDX, m_constant, 0, 360);
}


BEGIN_MESSAGE_MAP(CConstant0To360Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant0To360Dlg 메시지 처리기
