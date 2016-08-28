/* 
===============================================================================
The MIT License


Copyright (C) 1994-2015 simawei<simawei@qq.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===============================================================================
*/

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
