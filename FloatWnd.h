#pragma once

#include <Windows.h>

/************************************************************************/
/* 

	对Hwnd窗口做工作.透明.设置窗口大小,贴背景图.设置text

*/
/************************************************************************/
class CFloatWnd
{
public:
	CFloatWnd(void);
	~CFloatWnd(void);
	

	void Init(HWND hDlg,int x,int y);

	UINT MsgProc(HWND hDlg,UINT message, WPARAM wParam, LPARAM lParam);
	void SetMsg(char* d);

	void Paint(HDC hdc);
protected:

	 

	void CFloatWnd::GetBITMAPInfo(HBITMAP h,int& width,int& height);
	void CFloatWnd::OnUpdateTransparent(HWND hWnd ,int iTransparent);
	void CFloatWnd::RemoveWndTitleStyle(HWND hWnd);
	void CFloatWnd::AddWndTitleStyle(HWND hWnd);
	void CFloatWnd::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y);

	void CFloatWnd::CreateFont();

	 
private:
	HBITMAP  hBitmap;
	int m_width;
	int m_height;

	HWND m_hDlg;

	HFONT m_hFont;

	char msg[255];//msg

};
