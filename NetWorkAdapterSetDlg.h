#pragma once
#include "afxcmn.h"


// CNetWorkAdapterSetDlg �Ի���
/************************************************************************/
/* 
  
  ѡ�������Ի���

*/
/************************************************************************/
class CNetWorkAdapterSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetWorkAdapterSetDlg)

public:
	CNetWorkAdapterSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetWorkAdapterSetDlg();

// �Ի�������
	enum { IDD = IDD_NETWORKADAPTERSETDLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	int GetSelectedItem();
public:
	CListCtrl m_listctrl;
	afx_msg void OnBnClickedOk(); 
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
