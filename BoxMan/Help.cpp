// Help.cpp : 实现文件
//

#include "stdafx.h"
#include "BoxMan.h"
#include "Help.h"


// CHelp 对话框

IMPLEMENT_DYNAMIC(CHelp, CDialog)

CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CHelp::IDD, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_P, m_HelpCtrl);
}


BEGIN_MESSAGE_MAP(CHelp, CDialog)
END_MESSAGE_MAP()


// CHelp 消息处理程序
