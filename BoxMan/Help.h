#pragma once
#include "afxwin.h"


// CHelp 对话框

class CHelp : public CDialog
{
	DECLARE_DYNAMIC(CHelp)

public:
	CHelp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHelp();

// 对话框数据
	enum { IDD = IDD_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_HelpCtrl;
};
