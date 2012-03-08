#pragma once


// CBoxManWnd

class CBoxManWnd : public CWnd
{
	DECLARE_DYNAMIC(CBoxManWnd)

public:
	CBoxManWnd();
	virtual ~CBoxManWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnInitMenu(CMenu* pMenu);
protected:
	CMenu* m_pSubMenu;
public:
	afx_msg void OnMenuGameLevel();
public:
	afx_msg void OnMenuGameMusic();
public:
	afx_msg void OnMenuGameHelp();
public:
	afx_msg void OnAppExit();
};


