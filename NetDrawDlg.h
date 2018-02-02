#pragma once

#include "CurveDraw.h"

// CNetDrawDlg �Ի���
/************************************************************************/
/* 

  ��������ͼ�Ի���

*/
/************************************************************************/


class CNetDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetDrawDlg)

public:
	CNetDrawDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetDrawDlg();

// �Ի�������
	enum { IDD = IDD_NETDRAWDLG };

	BOOL OnInitDialog();
	void CNetDrawDlg::Draw();

	void Check();
	void CNetDrawDlg::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y);
	BOOL PreTranslateMessage(MSG* pMsg) ;

	int height;//����100kb/s ��λ�߶�

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



	DWORD in_speed;//����
	DWORD out_speed;//����
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public: 
};
