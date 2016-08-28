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


// NetDrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "networkmonitor.h"
#include "NetDrawDlg.h"
#include ".\netdrawdlg.h"


// CNetDrawDlg 对话框

IMPLEMENT_DYNAMIC(CNetDrawDlg, CDialog)
CNetDrawDlg::CNetDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetDrawDlg::IDD, pParent)
{
	height=1;
}

CNetDrawDlg::~CNetDrawDlg()
{
}

void CNetDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNetDrawDlg, CDialog)
 	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL CNetDrawDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message) 
	{ 
	case WM_LBUTTONDOWN:
		{
			POINTS pts = MAKEPOINTS(pMsg->lParam );   // position of cursor
			SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pts.x, pts.y));
			return(TRUE);
		}

	case WM_LBUTTONDBLCLK:
		if ( IsWindowVisible())
		{
			ShowWindow(SW_HIDE);
		}else{
			ShowWindow(SW_SHOW);
		}


		break;
	} 

	return CDialog::PreTranslateMessage(pMsg);


}

//0-255
void OnUpdateTransparent(HWND hWnd ,int iTransparent)
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

void GetBITMAPInfo(HBITMAP h,int& width,int& height)
{
	BITMAP bitmap ;
	::GetObject (h, sizeof (BITMAP), &bitmap) ;
	width=bitmap.bmWidth;
	height=bitmap.bmHeight;
}

BOOL CNetDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//配置文件读窗体xy
	int last_x=IniGetInt(FilePath,"window","pos2_x",0);
	int last_y=IniGetInt(FilePath,"window","pos2_y",0);
	 
	

	//窗体的背景图 //加载指定bmp,使用bmp默认宽高
 	hBitmap = NULL;// (HBITMAP)::LoadImage(NULL, "res//logo2.bmp" ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	if(hBitmap==NULL)
	{
		//AfxMessageBox("er");
		//从配置文件载入失败,从exe的默认资源加载
		//hBitmap  = ::LoadBitmap (::GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP2)) ;;// m_Logo.GetBitmap();
	}
 

	//得到bmp宽高
	//GetBITMAPInfo(hBitmap,m_width,m_height);
	m_width=IniGetInt(FilePath,"window","width",300);
	m_height=IniGetInt(FilePath,"window","height",200);


	// TODO: 在此添加额外的初始化代码
	
	up_R=IniGetInt(FilePath,"window","up_R",0);
	up_G=IniGetInt(FilePath,"window","up_G",255);
	up_B=IniGetInt(FilePath,"window","up_B",0);

	m_up.SetColor(RGB(up_R,up_G,up_B));

	download_R=IniGetInt(FilePath,"window","download_R",255);
	download_G=IniGetInt(FilePath,"window","download_G",0);
	download_B=IniGetInt(FilePath,"window","download_B",0); 

	m_download.SetColor(RGB(download_R,download_G,download_B));

	height=IniGetInt(FilePath,"window","height128kb",32);

    int Transparent=IniGetInt(FilePath,"window","Transparent2",255);

	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong( GetSafeHwnd() ,GWL_EXSTYLE)^0x80000);

 
	// 使窗口常居顶层
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,	SWP_NOSIZE|SWP_NOMOVE);
	//去标题栏
	//RemoveWndTitleStyle(this->GetSafeHwnd());

 
 
		//调节透明度
		OnUpdateTransparent(GetSafeHwnd(), Transparent);
	 
	 

  

	//窗体移动xy点,缩放成bmp大小
	MoveWindow(last_x,last_y, m_width+2, m_height+2,TRUE );
 

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CNetDrawDlg::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y)
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

void CNetDrawDlg::Draw()
{
	OnPaint();
}

void CNetDrawDlg::OnPaint() 
{
	CDialog::OnPaint();


	CDC *pDC=GetDC();  


//	CBitmapToHDC(pDC->GetSafeHdc(),hBitmap,0,0);
	
	CRect rect;
	GetClientRect(&rect);
	//------------------------------------
	//黑色背景
 
 	CBrush mybrush1;   //创建刷子
	mybrush1.CreateSolidBrush(RGB(0,0,0)); //设置刷子
 
	pDC->FillRect(rect,&mybrush1);//开始刷
 

	//---------------------------------------------------
 
	CPen pen(0,1,RGB(34,120,80)); 
	pDC->SelectObject(pen);

	//绘制y刻度
	pDC->MoveTo(0, rect.top);//最底
	pDC->LineTo(0,rect.bottom);

	rect.right-=3;

	//绘制x刻度
	pDC->MoveTo(1,rect.bottom);//最底
	pDC->LineTo(rect.right ,rect.bottom);

	int linecount=m_height/height;
	
	for (int i=1;i<=linecount;i++)
	{
		pDC->MoveTo(1,rect.bottom-height*i );//100 KB/S
		pDC->LineTo( rect.right ,rect.bottom-height*i );

	}

	//pDC->MoveTo(1,rect.bottom-height/2);//100 KB/S
	//pDC->LineTo( rect.right ,rect.bottom-height/2);

	//pDC->MoveTo(1,rect.bottom-height);//200 KB/S
	//pDC->LineTo( rect.right ,rect.bottom-height);

	//pDC->MoveTo(1,rect.bottom-height-height/2);//300 KB/S
	//pDC->LineTo( rect.right ,rect.bottom-height-height/2);

	//pDC->MoveTo(1,rect.bottom-height*2);//400 KB/S
	//pDC->LineTo(rect.right ,rect.bottom-height*2);

	//pDC->MoveTo(1,rect.bottom-height*2-height/2);//500 KB/S
	//pDC->LineTo(rect.right ,rect.bottom-height*2-height/2);


	//下载曲线
	m_download.Draw( rect ,pDC ,height);

	//上传曲线
	m_up.Draw( rect,pDC,height );


	ReleaseDC(pDC);
}

// CNetDrawDlg 消息处理程序
 

 