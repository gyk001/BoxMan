#include "StdAfx.h"
#include "BoxManMain.h"
#include "BoxMan.h"
CBoxManMain::CBoxManMain(void)
: m_SoundState(0)
{
}

CBoxManMain::~CBoxManMain(void)
{
}

void CBoxManMain::LoadMap(int iMissionNum)
{
	CString str;
	str.Format("[%d]",iMissionNum);
	FILE *pFile=fopen("MyBoxMan\\map.info","rt");
	if (pFile==NULL)
	{
		AfxMessageBox("载入地图文件失败！");
		return;
	}
	m_SoundState=SOUND_STATE_START;
	BoxManPlaySound();
	
	char cTmp[M_TAB_WIDTH*2];
	fgets(cTmp,M_TAB_WIDTH*2,pFile);
	while (strncmp(cTmp,str,3)!=0)
	{
		fgets(cTmp,M_TAB_WIDTH*2,pFile);
	}
	for (int i=0;i<M_TAB_WIDTH;i++)
	{
		fgets(m_cMap[i],M_TAB_WIDTH*2,pFile);

	}
	fclose(pFile);

}
void CBoxManMain::GetManPosition()
{
	int i,j;
	for (i=0;i<M_TAB_WIDTH;i++)
	{
		for (j=0;j<M_TAB_HEIGHT;j++)
		{
			if (m_cMap[i][j]==MAP_MANWALL||m_cMap[i][j]==MAP_MANBALL)
			{
				goto A;
			}
		}
	}
A:
	m_ptManPosition.x=j;
	m_ptManPosition.y=i;

}

void CBoxManMain::DispatchMsg(UINT nChar)
{
	int x1,y1,x2,y2,x3,y3;
	x1=m_ptManPosition.x;
	y1=m_ptManPosition.y;
	switch (nChar)
	{
	case VK_UP:
		x2=x1;
		y2=y1-1;
		x3=x1;
		y3=y1-2;
		UpdataMap(x1,y1,x2,y2,x3,y3);

		break;
	case VK_DOWN:
		x2=x1;
		y2=y1+1;
		x3=x1;
		y3=y1+2;
		UpdataMap(x1,y1,x2,y2,x3,y3);
		break;
	case VK_LEFT:
		x2=x1-1;
		y2=y1;
		x3=x1-2;
		y3=y1;
		UpdataMap(x1,y1,x2,y2,x3,y3);
		break;
	case VK_RIGHT:
		x2=x1+1;
		y2=y1;
		x3=x1+2;
		y3=y1;
		UpdataMap(x1,y1,x2,y2,x3,y3);
		break;
	case 82://R
	case 114://r
		LoadMap(m_iMissionNum);
		GetManPosition();
		m_pBoxManWnd->Invalidate(FALSE);
		
		break;
	case 113://F2
		m_iMissionNum=m_iMissionNum+1;
		if (m_iMissionNum>MAX_MISSION_NUM)
		{
			m_iMissionNum=1;
		}
		LoadMap(m_iMissionNum);
		GetManPosition();
		m_pBoxManWnd->Invalidate(FALSE);

		break;
	case 112://F1

		m_iMissionNum=m_iMissionNum-1;
		if (m_iMissionNum<1)
		{
			m_iMissionNum=MAX_MISSION_NUM;
		}
		LoadMap(m_iMissionNum);
		GetManPosition();
		m_pBoxManWnd->Invalidate(FALSE);

		break;
	}
	WinOrNot();
}

void CBoxManMain::UpdataMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
	switch (m_cMap[y2][x2])
	{
	case MAP_BACKGROUP:
		AfxMessageBox("wrong map!");
		break;
	case MAP_WHITEWALL:
	
		break;
	case MAP_BLUEWALL:
		m_cMap[y2][x2]=MAP_MANWALL;
		if (m_cMap[y1][x1]==MAP_MANWALL)
		{
			m_cMap[y1][x1]=MAP_BLUEWALL;
		} 
		else if(m_cMap[y1][x1]==MAP_MANBALL)
		{
			m_cMap[y1][x1]=MAP_BALL;
		}
		m_ptManPosition.x=x2;
		m_ptManPosition.y=y2;
		m_SoundState=SOUND_STATE_MOVE;
		break;
	case MAP_BALL:
		m_cMap[y2][x2]=MAP_MANBALL;
		if (m_cMap[y1][x1]==MAP_MANWALL)
		{
			m_cMap[y1][x1]=MAP_BLUEWALL;
		}
		else if (m_cMap[y1][x1]==MAP_MANBALL)
		{
			m_cMap[y1][x1]=MAP_BALL;
		}
		m_ptManPosition.x=x2;
		m_ptManPosition.y=y2;
		m_SoundState=SOUND_STATE_MOVE;
		break;
	case MAP_YELLOWBOX:
		if(m_cMap[y3][x3]==MAP_BALL)
		{
			m_cMap[y3][x3]=MAP_REDBOX;
			m_cMap[y2][x2]=MAP_MANWALL;
			if (m_cMap[y1][x1]==MAP_MANWALL)
			{
				m_cMap[y1][x1]=MAP_BLUEWALL;
			}
			else if (m_cMap[y1][x1]==MAP_MANBALL)
			{
				m_cMap[y1][x1]=MAP_BALL;
			}
			m_ptManPosition.x=x2;
			m_ptManPosition.y=y2;
			m_SoundState=SOUND_STATE_PUSH;
		}
		else if (m_cMap[y3][x3]==MAP_BLUEWALL)
		{
			m_cMap[y3][x3]=MAP_YELLOWBOX;
			m_cMap[y2][x2]=MAP_MANWALL;
			if (m_cMap[y1][x1]==MAP_MANWALL)
			{
				m_cMap[y1][x1]=MAP_BLUEWALL;
			}
			else if (m_cMap[y1][x1]==MAP_MANBALL)
			{
				m_cMap[y1][x1]=MAP_BALL;
			}
			m_ptManPosition.x=x2;
			m_ptManPosition.y=y2;
			m_SoundState=SOUND_STATE_PUSH;

		}
		break;
	case MAP_REDBOX:
		if (m_cMap[y3][x3]==MAP_BALL)
		{
			m_cMap[y3][x3]=MAP_REDBOX;
			m_cMap[y2][x2]=MAP_MANBALL;
			if (m_cMap[y1][x1]==MAP_MANWALL)
			{	
				m_cMap[y1][x1]=MAP_BLUEWALL;
			}
			else if (m_cMap[y1][x1]==MAP_MANBALL)
			{
				m_cMap[y1][x1]=MAP_BALL;
			}
			m_ptManPosition.x=x2;
			m_ptManPosition.y=y2;
			m_SoundState=SOUND_STATE_PUSH;
		}
		else if (m_cMap[y3][x3]==MAP_BLUEWALL)
		{
			m_cMap[y3][x3]=MAP_YELLOWBOX;
			m_cMap[y2][x2]=MAP_MANBALL;
			if (m_cMap[y1][x1]==MAP_MANWALL)
			{
				m_cMap[y1][x1]=MAP_BLUEWALL;
			} 
			else if(m_cMap[y1][x1]==MAP_MANBALL)
			{
				m_cMap[y1][x1]=MAP_BALL;
			}
			m_ptManPosition.x=x2;
			m_ptManPosition.y=y2;
			m_SoundState=SOUND_STATE_PUSH;

		}
		break;
	case MAP_MANWALL:
		AfxMessageBox("wwrong map!");
		break;
	case MAP_MANBALL:
		AfxMessageBox("wwrong map!");
		break;
	}
	m_pBoxManWnd->Invalidate(FALSE);
	BoxManPlaySound();

}

void CBoxManMain::DrawGameArea(CDC* pDC)
{
	int i,j,x,y;
	for (i=0;i<M_TAB_HEIGHT;i++)
	{
		for (j=0;j<M_TAB_WIDTH;j++)
		{
			x=j*BLOCK_WIDTH;
			y=i*BLOCK_HEIGHT;
			switch (m_cMap[i][j])
			{
			case MAP_BACKGROUP:
				DrawBackGroup(x,y,pDC);
				break;
			case MAP_WHITEWALL:
				DrawWhiteWall(x,y,pDC);
				break;
			case MAP_BLUEWALL:
				DrawBlueWall(x,y,pDC);
				break;
			case MAP_BALL:
				DrawBall(x,y,pDC);
				break;
			case MAP_YELLOWBOX:
				DrawYellowBox(x,y,pDC);
				break;
			case MAP_REDBOX:
				DrawRedBox(x,y,pDC);
				break;
			case MAP_MANWALL:
				DrawManWall(x,y,pDC);
				break;
			case MAP_MANBALL:
				DrawManBall(x,y,pDC);
				break;
			}
			
		}
	}
	COLORREF clrOldText=pDC->GetTextColor();
	int BkOldModle=pDC->GetBkMode();
	pDC->SetTextColor(RGB(102,0,0));
	pDC->SetBkMode(TRANSPARENT);
	CString sTmp;
	sTmp.Format("当前关数：%d",m_iMissionNum);
	pDC->TextOut(50,382,sTmp);
	pDC->SetTextColor(clrOldText);
	pDC->SetBkMode(BkOldModle);
}

void CBoxManMain::DrawBackGroup(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(0,0,0);
	pDC->FillSolidRect(x,y,BLOCK_WIDTH,BLOCK_WIDTH,clr);
}

void CBoxManMain::DrawWhiteWall(int x, int y, CDC* pDC)
{
	COLORREF clr1=RGB(255,255,255);
	COLORREF clr2=RGB(48,48,48);
	COLORREF clr3=RGB(192,192,192);
	pDC->FillSolidRect(x,y,19,19,clr1);
	pDC->FillSolidRect(x+1,y+1,19,19,clr2);
	pDC->FillSolidRect(x+1,y+1,18,18,clr3);
	pDC->MoveTo(x,y+10);
	pDC->LineTo(x+20,y+10);
	pDC->MoveTo(x+10,y+10);
	pDC->LineTo(x+10,y+20);
}

void CBoxManMain::DrawBlueWall(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(0,0,255);
	COLORREF clr2=RGB(48,48,48);
	pDC->FillSolidRect(x,y,20,20,clr2);
		pDC->FillSolidRect(x+1,y+1,19,19,clr);
	pDC->MoveTo(x,y+10);
	pDC->LineTo(x+20,y+10);
	pDC->MoveTo(x+10,y+10);
	pDC->LineTo(x+10,y+20);
}

void CBoxManMain::DrawYellowBox(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(255,255,0);
	pDC->FillSolidRect(x,y,20,20,clr);
	COLORREF clr2=RGB(255,192,0);
	pDC->FillSolidRect(x+2,y+2,16,16,clr2);
	COLORREF clr3=RGB(0,0,0);
	pDC->SetPixel(x+3,y+3,clr3);
	pDC->SetPixel(x+17,y+3,clr3);
	pDC->SetPixel(x+3,y+17,clr3);
	pDC->SetPixel(x+17,y+17,clr3);
}
void CBoxManMain::DrawManBall(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(0,0,255);
	COLORREF clr2=RGB(48,48,48);
	pDC->FillSolidRect(x,y,20,20,clr2);
	pDC->FillSolidRect(x+1,y+1,19,19,clr);

	pDC->Ellipse(x,y,x+20,y+20);
	pDC->Ellipse(x+5,y+5,x+15,y+15);
	pDC->Ellipse(x+6,y+2,x+14,y+10);
	pDC->MoveTo(x+2,y+11);
	pDC->LineTo(x+18,y+11);
	pDC->MoveTo(x+10,y+10);
	pDC->LineTo(x+10,y+12);
	pDC->MoveTo(x+2,y+20);
	pDC->LineTo(x+10,y+12);
	pDC->LineTo(x+18,y+20);
}

void CBoxManMain::DrawBall(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(0,0,255);
	COLORREF clr2=RGB(48,48,48);
	pDC->FillSolidRect(x,y,20,20,clr2);
	pDC->FillSolidRect(x+1,y+1,19,19,clr);

	pDC->Ellipse(x,y,x+20,y+20);
	pDC->Ellipse(x+5,y+5,x+15,y+15);
}

void CBoxManMain::DrawRedBox(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(0,255,0);
	COLORREF clr2=RGB(255,0,0);
	pDC->FillSolidRect(x,y,20,20,clr);
	pDC->FillSolidRect(x+2,y+2,16,16,clr2);
}

void CBoxManMain::DrawManWall(int x, int y, CDC* pDC)
{
	COLORREF clr=RGB(0,0,255);
	COLORREF clr2=RGB(48,48,48);
	pDC->FillSolidRect(x,y,20,20,clr2);
	pDC->FillSolidRect(x+1,y+1,19,19,clr);
	pDC->Ellipse(x+6,y+2,x+14,y+10);
	pDC->MoveTo(x+2,y+11);
	pDC->LineTo(x+18,y+11);
	pDC->MoveTo(x+10,y+10);
	pDC->LineTo(x+10,y+12);
	pDC->MoveTo(x+2,y+20);
	pDC->LineTo(x+10,y+12);
	pDC->LineTo(x+18,y+20);
}
void CBoxManMain::MyInit(void)
{
	m_bSound=true;//音效开启
	m_iMissionNum=1;
	MAX_MISSION_NUM=LoadMaxMissionNum();
	LoadMap(m_iMissionNum);
	GetManPosition();
}

bool CBoxManMain::IsFinish(void)
{
	bool bFinish=true;
	for (int i=0;i<M_TAB_HEIGHT;i++)
	{
		for (int j=0;j<M_TAB_WIDTH;j++)
		{
			if (m_cMap[i][j]==MAP_BALL||m_cMap[i][j]==MAP_MANBALL)
			{
				bFinish=false;
			}
		}
	}
	return bFinish;
}

int CBoxManMain::LoadMaxMissionNum(void)
{
	int iMissionNum=1;
	CString str;
	str.Format("[%d]",iMissionNum);
	FILE *pFile=fopen("MyBoxMan\\map.info","rb");
	if (pFile==NULL)
	{
		AfxMessageBox("载入地图文件失败！");
		return -1;
	}
	char cTmp[20];
	while (!feof(pFile))
	{
		fgets(cTmp,20,pFile);
		if(strncmp(cTmp,str,3)==0)
		{
			str.Format("[%d]",++iMissionNum);
		}
	}
	fclose(pFile);
	return iMissionNum-1;
}

void CBoxManMain::WinOrNot(void)
{
	if (IsFinish())
	{
		m_pBoxManWnd->Invalidate(FALSE);
		m_SoundState=SOUND_STATE_VICTORY;
		BoxManPlaySound();
		AfxMessageBox("恭喜！\n您已通过该关！");
		//Sleep(1000);
		DispatchMsg(113);
	}
}

void CBoxManMain::BoxManPlaySound(void)
{
	if (m_bSound)
	{
		char strFileName[30]="";	
		switch (m_SoundState)
		{
		case SOUND_STATE_MOVE:
			strcpy(strFileName,"MyBoxMan\\move.wav");
			break;
		case SOUND_STATE_PUSH:
			strcpy(strFileName,"MyBoxMan\\push.wav");
			break;
		case SOUND_STATE_VICTORY:
			strcpy(strFileName,"MyBoxMan\\victory.wav");
			break;
		case SOUND_STATE_START:
			strcpy(strFileName,"MyBoxMan\\start.wav");
			break;
		}
		PlaySound(strFileName,NULL,SND_ASYNC|SND_FILENAME);
	}
}
