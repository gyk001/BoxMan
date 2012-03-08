// BoxManWnd.cpp : 实现文件
//
//#pragma comment(lib,"Winmm.lib") 
#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManMain.h"
#include "BoxManWnd.h"
#include "Help.h"
#include "LoadMap.h"
//#include "Mmsystem.h"


// CBoxManWnd

IMPLEMENT_DYNAMIC(CBoxManWnd, CWnd)

CBoxManWnd::CBoxManWnd()
: m_pSubMenu(NULL)
{


}

CBoxManWnd::~CBoxManWnd()
{
}


BEGIN_MESSAGE_MAP(CBoxManWnd, CWnd)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_INITMENU()
	ON_COMMAND(ID_MENU_GAME_LEVEL, &CBoxManWnd::OnMenuGameLevel)
	ON_COMMAND(ID_MENU_GAME_MUSIC, &CBoxManWnd::OnMenuGameMusic)
	ON_COMMAND(ID_MENU_GAME_HELP, &CBoxManWnd::OnMenuGameHelp)
	ON_COMMAND(ID_APP_EXIT, &CBoxManWnd::OnAppExit)
END_MESSAGE_MAP()



// CBoxManWnd 消息处理程序



void CBoxManWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	theBoxMan.DispatchMsg(nChar);
	//CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	//theBoxMan.WinOrNot();


}

void CBoxManWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	CDC dcMemory;
	CBitmap bitmap;

	if (!dc.IsPrinting())
	{
		if (dcMemory.CreateCompatibleDC(&dc))
		{
			if (bitmap.CreateCompatibleBitmap(&dc,m_rcClient.right,m_rcClient.bottom))
			{
				dcMemory.SelectObject(&bitmap);
				theBoxMan.DrawGameArea(&dcMemory);
				dc.BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}




}

void CBoxManWnd::OnInitMenu(CMenu* pMenu)
{
	CWnd::OnInitMenu(pMenu);

	if((m_pSubMenu=pMenu->GetSubMenu(0))==0)
	{
		AfxMessageBox("初始化菜单失败!");
		PostQuitMessage(0);
	}
	if(m_bSound)
		m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC,MF_CHECKED|MF_BYCOMMAND);
	// TODO: 在此处添加消息处理程序代码
}

void CBoxManWnd::OnMenuGameLevel()
{
	// TODO: 在此添加命令处理程序代码
	CLoadMap dlg;
	dlg.strMaxNum.Format("当前最大关数:%d",MAX_MISSION_NUM );
	if (dlg.DoModal()==IDOK)
	{
		m_iMissionNum=dlg.m_LoadMapNum;
		theBoxMan.LoadMap(m_iMissionNum);
		Invalidate(true);
	}
}

void CBoxManWnd::OnMenuGameMusic()
{
	// TODO: 在此添加命令处理程序代码
	

	if (m_pSubMenu)
	{
		if (m_bSound==true)
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC,MF_UNCHECKED|MF_BYCOMMAND);
		else
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC,MF_CHECKED|MF_BYCOMMAND);

	}
	m_bSound=!m_bSound;
}

void CBoxManWnd::OnMenuGameHelp()
{
	// TODO: 在此添加命令处理程序代码
	CHelp dlg;
	//CRect a;
	//GetClientRect(&a);
	//dlg.m_HelpCtrl.MoveWindow(&a,1);
	dlg.DoModal();
}

void CBoxManWnd::OnAppExit()
{
	// TODO: 在此添加命令处理程序代码
	PostQuitMessage(0);
}

