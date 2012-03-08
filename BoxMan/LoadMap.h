#pragma once


// CLoadMap 对话框

class CLoadMap : public CDialog
{
	DECLARE_DYNAMIC(CLoadMap)

public:
	CLoadMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadMap();

// 对话框数据
	enum { IDD = IDD_LOAD_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_LoadMapNum;
public:
	CString strMaxNum;
};
