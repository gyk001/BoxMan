// BoxMan.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManWnd.h"
#include "BoxManMain.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBoxManApp

BEGIN_MESSAGE_MAP(CBoxManApp, CWinApp)

END_MESSAGE_MAP()


// CBoxManApp 构造

CBoxManApp::CBoxManApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

CBoxManApp::~CBoxManApp()
{
	delete m_pBoxManWnd;
	m_pBoxManWnd=NULL;
}
// 唯一的一个 CBoxManApp 对象

CBoxManApp theApp;
CBoxManMain theBoxMan;
int m_iMissionNum;
int MAX_MISSION_NUM;
CBoxManWnd* m_pBoxManWnd;
bool m_bSound;



// CBoxManApp 初始化

BOOL CBoxManApp::InitInstance()
{
	
	m_pBoxManWnd=new CBoxManWnd();
	WNDCLASS wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance=AfxGetInstanceHandle();
	wc.lpfnWndProc=::DefWindowProc;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor=LoadCursor(IDC_WAIT);
	wc.hIcon=LoadIcon(IDR_MAINFRAME);
	wc.lpszMenuName=MAKEINTRESOURCE(IDR_MAINFRAME);
	wc.lpszClassName="MyBoxMan";

	if (!AfxRegisterClass(&wc))
	{
		AfxMessageBox("注册窗口类失败！");
		return FALSE;
	}
	UINT uWidth=400+DEFAULT_FRAME_X;
	UINT uHeight=400+DEFAULT_FRAME_Y;
	UINT uXPos=GetSystemMetrics(SM_CXSCREEN)/2-uWidth/2;
	UINT uYPos=GetSystemMetrics(SM_CYSCREEN)/2-uHeight/2;
	if (!m_pBoxManWnd->CreateEx(NULL,wc.lpszClassName,"推箱子",WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,uXPos,uYPos,uWidth,uHeight,NULL,NULL))
	{
		AfxMessageBox("创建主窗口失败！");
		return false;
	}
	m_pMainWnd=m_pBoxManWnd;
	theBoxMan.MyInit();
	m_pBoxManWnd->ShowWindow(SW_NORMAL);
	return TRUE;
}
