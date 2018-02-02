#pragma once
#include "afxcmn.h"


// CNetWorkAdapterSetDlg 对话框
/************************************************************************/
/* 
  
  选择网卡对话框

*/
/************************************************************************/
class CNetWorkAdapterSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetWorkAdapterSetDlg)

public:
	CNetWorkAdapterSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetWorkAdapterSetDlg();

// 对话框数据
	enum { IDD = IDD_NETWORKADAPTERSETDLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	int GetSelectedItem();
public:
	CListCtrl m_listctrl;
	afx_msg void OnBnClickedOk(); 
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
