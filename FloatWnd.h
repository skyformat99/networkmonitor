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
