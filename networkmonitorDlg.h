// networkmonitorDlg.h : 头文件
//

#pragma once


#include "FloatWnd.h"

class CFloatWnd;
class CAboutDlg;

#include "NetDrawDlg.h"

// CnetworkmonitorDlg 对话框
class CnetworkmonitorDlg : public CDialog
{
// 构造
public:
	int OnHOTKEY();
	LRESULT   CnetworkmonitorDlg::WindowProc(UINT   message,   WPARAM   wParam,   LPARAM   lParam) ;

	CnetworkmonitorDlg(CWnd* pParent = NULL);	// 标准构造函数
 
// 对话框数据
	enum { IDD = IDD_NETWORKMONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CToolTipCtrl m_openToolTip; 

	CFloatWnd m_floatWnd;

	void Check();
 
	BOOL CnetworkmonitorDlg::PreTranslateMessage(MSG* pMsg) ;

	void CnetworkmonitorDlg::OnRButtonUp(UINT nFlags, CPoint point) ;
	void CnetworkmonitorDlg::OnExit() ;
	void CnetworkmonitorDlg::OnShow() ;
	void CnetworkmonitorDlg::On32776();

	CNetDrawDlg m_drawDlg;
// 实现
protected:


	int TipTextColorR ;
	int TipTextColorG ;
	int TipTextColorB ;

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
