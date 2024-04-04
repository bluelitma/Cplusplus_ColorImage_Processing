// Constant0To255.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageAlpha1.h"
#include "afxdialogex.h"
#include "Constant0To255.h"


// CConstant0To255 대화 상자

IMPLEMENT_DYNAMIC(CConstant0To255, CDialog)

CConstant0To255::CConstant0To255(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_0TO255, pParent)
	, m_constant(0)
{

}

CConstant0To255::~CConstant0To255()
{
}

void CConstant0To255::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxDouble(pDX, m_constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstant0To255, CDialog)
END_MESSAGE_MAP()


// CConstant0To255 메시지 처리기
