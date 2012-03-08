// LoadMap.cpp : 实现文件
//

#include "stdafx.h"
#include "BoxMan.h"
#include "LoadMap.h"
#include "BoxManMain.h"


// CLoadMap 对话框

IMPLEMENT_DYNAMIC(CLoadMap, CDialog)

CLoadMap::CLoadMap(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadMap::IDD, pParent)
	, m_LoadMapNum(1)
	, strMaxNum(_T(""))
{

}

CLoadMap::~CLoadMap()
{
}

void CLoadMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOAD_NUM, m_LoadMapNum);
	DDV_MinMaxUInt(pDX, m_LoadMapNum, 1,MAX_MISSION_NUM);
	DDX_Text(pDX, IDC_STATIC_MAX_NUM, strMaxNum);
}


BEGIN_MESSAGE_MAP(CLoadMap, CDialog)
END_MESSAGE_MAP()


// CLoadMap 消息处理程序
