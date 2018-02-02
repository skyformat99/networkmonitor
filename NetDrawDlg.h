#pragma once

#include "CurveDraw.h"

// CNetDrawDlg 对话框
/************************************************************************/
/* 

  绘制曲线图对话框

*/
/************************************************************************/


class CNetDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetDrawDlg)

public:
	CNetDrawDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetDrawDlg();

// 对话框数据
	enum { IDD = IDD_NETDRAWDLG };

	BOOL OnInitDialog();
	void CNetDrawDlg::Draw();

	void Check();
	void CNetDrawDlg::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y);
	BOOL PreTranslateMessage(MSG* pMsg) ;

	int height;//绘制100kb/s 单位高度

	CCurveDraw m_download;
	CCurveDraw m_up;

	int up_R;
	int up_G;
	int up_B;
	int download_R;
	int download_G;
	int download_B;

	HBITMAP hBitmap;
	int m_width,m_height;



	DWORD in_speed;//下行
	DWORD out_speed;//上行
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public: 
};
