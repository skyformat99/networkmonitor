// networkmonitorDlg.h : ͷ�ļ�
//

#pragma once


#include "FloatWnd.h"

class CFloatWnd;
class CAboutDlg;

#include "NetDrawDlg.h"

// CnetworkmonitorDlg �Ի���
class CnetworkmonitorDlg : public CDialog
{
// ����
public:
	int OnHOTKEY();
	LRESULT   CnetworkmonitorDlg::WindowProc(UINT   message,   WPARAM   wParam,   LPARAM   lParam) ;

	CnetworkmonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��
 
// �Ի�������
	enum { IDD = IDD_NETWORKMONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CToolTipCtrl m_openToolTip; 

	CFloatWnd m_floatWnd;

	void Check();
 
	BOOL CnetworkmonitorDlg::PreTranslateMessage(MSG* pMsg) ;

	void CnetworkmonitorDlg::OnRButtonUp(UINT nFlags, CPoint point) ;
	void CnetworkmonitorDlg::OnExit() ;
	void CnetworkmonitorDlg::OnShow() ;
	void CnetworkmonitorDlg::On32776();

	CNetDrawDlg m_drawDlg;
// ʵ��
protected:


	int TipTextColorR ;
	int TipTextColorG ;
	int TipTextColorB ;

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
