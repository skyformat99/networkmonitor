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


#include "StdAfx.h"
#include ".\floatwnd.h"
#include "resource.h"

void TextOutToHDC(HDC hdc,int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor)
{
	//内存dc选择位图
	HGDIOBJ h=SelectObject(hdc,m_hFont);

	SetBkColor(hdc, RGB(0,0,0));//黑色背景
	SetTextColor(hdc, fontColor );      /**< 字体颜色 */

	//SetBkMode(hdc, OPAQUE);                     /**< 用当前的背景颜色填充背景 */
	SetBkMode(hdc,TRANSPARENT);

	TextOut(hdc,x, y, msg, strlen(msg));	   /**< 输出文字到暂存hDC */

	SelectObject(hdc,h);

}


CFloatWnd::CFloatWnd(void)
{ 
}

CFloatWnd::~CFloatWnd(void)
{
}

void CFloatWnd::GetBITMAPInfo(HBITMAP h,int& width,int& height)
{
	BITMAP bitmap ;
	::GetObject (h, sizeof (BITMAP), &bitmap) ;
	width=bitmap.bmWidth;
	height=bitmap.bmHeight;
}

//0-255
void CFloatWnd::OnUpdateTransparent(HWND hWnd ,int iTransparent)
{

	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			//SetLayeredWindowAttributes( RGB(255,0,255),iTransparent,ULW_COLORKEY|LWA_ALPHA);//LWA_ALPHA
			//RGB(255,0,255)

			pFun(hWnd,RGB(255,0,255),iTransparent,1|2);//ULW_COLORKEY 1表示要用透明色把指定色不显示,LWA_ALPHA 2表示要控制半透明
		}
		FreeLibrary(hInst); 
	}
}

//去掉窗体的标题栏风格
void CFloatWnd::RemoveWndTitleStyle(HWND hWnd)
{
	long   dwStyle   =   GetWindowLong(hWnd,   GWL_STYLE); 
	dwStyle   &=   ~(WS_CAPTION); 

	SetWindowLong(hWnd,   GWL_STYLE,   dwStyle); 
}

// 窗体的标题栏风格
void CFloatWnd::AddWndTitleStyle(HWND hWnd)
{
	long   dwStyle   =   GetWindowLong(hWnd,   GWL_STYLE); 
	dwStyle   |=  (WS_CAPTION); 

	SetWindowLong(hWnd,   GWL_STYLE,   dwStyle); 
}

void CFloatWnd::CreateFont()
{
	/** 创建字体 */
	m_hFont = ::CreateFont(12,   /**< 字体高度 */
		0,						/**< 字体宽度 */
		0,						/**< 字体的旋转角度  */
		0,						/**< 字体底线的旋转角度 */
		FW_NORMAL,				/**< 字体的重量 */
		FALSE,					/**< 是否使用斜体 */
		FALSE,					/**< 是否使用下划线 */
		FALSE,					/**< 是否使用删除线 */
		GB2312_CHARSET,			/**< 设置字符集 */
		OUT_TT_PRECIS,			/**< 输出精度 */
		CLIP_DEFAULT_PRECIS,	/**< 裁剪精度 */
		ANTIALIASED_QUALITY,	/**< 输出质量 */
		FF_DONTCARE|DEFAULT_PITCH,		/**< Family And Pitch */
		"宋体");				/**< 字体名称 */

}

void CFloatWnd::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y)
{
 

	//创建兼容设备的内存dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//内存dc选择位图
	SelectObject(hdcMem,hbmp);

	BitBlt(hdc,
		pic_x, pic_y, //指定hdc左上角
		m_width,m_height,  //bmp宽高
		hdcMem, 
		0,0,  //hdcMem的xy,所以这里从左上角复制图片到内存dc
		SRCCOPY); //把屏幕图象copy
	//删除内存dc
	DeleteDC(hdcMem);
}

 
void CFloatWnd::Init(HWND hDlg,int x,int y)
{
	this->m_hDlg=hDlg;

	// 使窗口常居顶层
	::SetWindowPos(hDlg,HWND_TOPMOST,0,0,0,0,	SWP_NOSIZE|SWP_NOMOVE);

	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(hDlg,GWL_EXSTYLE,GetWindowLong( hDlg ,GWL_EXSTYLE)^0x80000);

	//去标题栏
	RemoveWndTitleStyle(hDlg);
	//AddWndTitleStyle(hDlg);

 
	CString bgimg=IniGetString(FilePath,"window","bkimg");
    int Transparent=IniGetInt(FilePath,"window","Transparent",255);
  
	//窗体的背景图 //加载指定bmp,使用bmp默认宽高
	hBitmap = (HBITMAP)::LoadImage(NULL, bgimg ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	if(hBitmap==NULL)
	{
		//AfxMessageBox("er");
		//从配置文件载入失败,从exe的默认资源加载
		hBitmap  = ::LoadBitmap (::GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1)) ;;// m_Logo.GetBitmap();
	}


	//得到bmp宽高
	GetBITMAPInfo(hBitmap,m_width,m_height);

	//窗体移动xy点,缩放成bmp大小
	MoveWindow(hDlg,x,y, m_width,  m_height,TRUE );

	 
    //调节透明度
    OnUpdateTransparent(hDlg, Transparent );
 
	 

	//创建字体
	CreateFont();

}

BYTE r=255;
BYTE g=255;
BYTE b=255;
void CFloatWnd::Paint(HDC hdc)
{
//	HDC hdc=::GetDC(hDlg);  //得到handle

	//绘制背景图片
	CBitmapToHDC(hdc,hBitmap,0,0);

	//输出字
	TextOutToHDC(hdc,
		10,  //字输出的x坐标
		m_height/2/2, //字输出的y坐标
		msg,m_hFont,RGB(r,g,b));

//	::ReleaseDC(hDlg,hdc); //释放hdc
}

void CFloatWnd::SetMsg(char* d)
{
	strcpy(msg,d);

	HDC hdc=::GetDC(m_hDlg);  //得到handle
	
	Paint(hdc);
	//	Invalidate(1);
		
	::ReleaseDC(m_hDlg,hdc); //释放hdc
}
 

UINT   CFloatWnd::MsgProc(HWND hDlg, //对话框句柄
						  UINT message, //消息类型
						  WPARAM wParam, //消息附带信息
						  LPARAM lParam) //消息附带信息
{
	switch(message) // 消息处理
	{
/*	case WM_CREATE:
	case WM_INITDIALOG: //对话框初始化消息
		{
			Init(hDlg,0,0);
			return(TRUE);
		}
 	case WM_PAINT:
		{ 
			PAINTSTRUCT ps;
			HDC hdc;
			hdc   =   BeginPaint(hDlg,&ps); 

			Paint(hdc);

			//InvalidateRect(hWnd,NULL,true); 
			EndPaint(hDlg,&ps); 
 
			return(TRUE);
		}*/
 
	case WM_LBUTTONDOWN:
		{
			POINTS pts = MAKEPOINTS(lParam);   // position of cursor
			SendMessage(hDlg,WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pts.x, pts.y));
			return(TRUE);
		}
 
	case WM_LBUTTONDBLCLK:
		{
			printf("WM_LBUTTONDBLCLK\n");
			 

			return TRUE;
		}
	}
	return(FALSE); //对于没有处理的消息,返回FALSE
}
