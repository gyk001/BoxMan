#pragma once
#include "BoxManDef.h"


class CBoxManMain  
{
public:
	CBoxManMain(void);
	~CBoxManMain(void);
protected:
	char m_cMap[M_TAB_WIDTH][M_TAB_HEIGHT];
	CPoint m_ptManPosition;
public:
	void LoadMap(int iMissionNum);
	void DispatchMsg(UINT nChar);
	void GetManPosition();
public:
	void UpdataMap(int x1, int y1, int x2, int y2, int x3, int y3);
public:
	int m_SoundState;
public:
	void DrawGameArea(CDC* pDC);
public:
	void DrawBackGroup(int x, int y, CDC* pDC);
public:
	void DrawWhiteWall(int x, int y, CDC* pDC);
public:
	void DrawBlueWall(int x, int y, CDC* pDC);
public:
	void DrawYellowBox(int x, int y, CDC* pDC);
public:
	void DrawManBall(int x, int y, CDC* pDC);
public:
	void DrawBall(int x, int y, CDC* pDC);
public:
	void DrawRedBox(int x, int y, CDC* pDC);
public:
	void DrawManWall(int x, int y, CDC* pDC);
protected:

public:
	void MyInit(void);
public:
	bool IsFinish(void);
public:
	int LoadMaxMissionNum(void);
public:
	void WinOrNot(void);
public:
	void BoxManPlaySound(void);
};
extern CBoxManMain theBoxMan;
extern int MAX_MISSION_NUM;
