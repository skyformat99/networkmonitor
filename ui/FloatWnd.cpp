// FloatWnd.cpp : implementation file
//

//#include "stdafx.h"

#include "FloatWnd.h"
 

// 读数字
int IniGetInt(  char *strFile, char *lpAppName, char *lpKeyName )
{
	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //读
	if(ret==0){
		//MessageBox(0,"ini读int失败!","",0);
		return -1;
	}else{
		ret=atoi(inBuf);
		return ret;
	}

}

CString IniGetString(  char *strFile, char *lpAppName, char *lpKeyName )
{
	CString str;

	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //读
	if(ret==0)
	{
		//MessageBox(0,"ini读int失败!","",0);
	}else{
		str=inBuf; 
	}

	return str;
}
void GetBITMAPInfo(HBITMAP h,int& width,int& height)
{
	BITMAP bitmap ;
	::GetObject (h, sizeof (BITMAP), &bitmap) ;
	width=bitmap.bmWidth;
	height=bitmap.bmHeight;
}

void GetBITMAPInfo2(HBITMAP h,int& width,int& height)
{
	CBitmap b;
	b.Attach(h);
	BITMAP bmp;
	b.GetBitmap(&bmp);

	width = bmp.bmWidth;
	height = bmp.bmHeight;
}

void GetBITMAPInfo(CBitmap b,int& width,int& height)
{
	BITMAP bmp;
	b.GetBitmap(&bmp);
	width = bmp.bmWidth;
	height = bmp.bmHeight;
}
 


/////////////////////////////////////////////////////////////////////////////
// CFloatWnd dialog


CFloatWnd::CFloatWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloatWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	AfxMessageBox("c");
	Create(CFloatWnd::IDD,pParent);
	ShowWindow(SW_SHOW);


	OnUpdateTransparent(255);

}


void CFloatWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloatWnd)
	//DDX_Control(pDX, IDC_LOGO, m_Logo);
	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDC_CloseBtn, m_CloseBtnPicCtrl);
}


BEGIN_MESSAGE_MAP(CFloatWnd, CDialog)
	//{{AFX_MSG_MAP(CFloatWnd)	
	ON_WM_PAINT()
 
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_32776, On32776)
	ON_COMMAND(ID_SELECT, OnShow)
	ON_WM_NCLBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd message handlers

BOOL CFloatWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message) 
	{ 
	case WM_LBUTTONDOWN: 
	case WM_LBUTTONUP: 
	case WM_MOUSEMOVE: 
		m_openToolTip.RelayEvent(pMsg); 
	} 

	return CDialog::PreTranslateMessage(pMsg);
} 

 

#include "../NetStat.h"

char FilePath[255]=".\\config.ini"; 
extern CNetStat cnet;
BOOL CFloatWnd::OnInitDialog() 
{
	CDialog::OnInitDialog();
 
	m_openToolTip.Create(this);  
	m_openToolTip.AddTool( this , "" ); 
	m_openToolTip.SetDelayTime(200); 
	m_openToolTip.SetTipTextColor( RGB(0,0,255) ); 
	m_openToolTip.SetTipBkColor( RGB(255,255,255)); 
	m_openToolTip.Activate(TRUE); 
	m_openToolTip.SetMaxTipWidth(250);  

	 

	SetMsg("初始化中...");//千千静听

	// TODO: Add extra initialization here
	
	//配置文件读指定网卡index
	int AdapterIndex=IniGetInt(FilePath,"network","AdapterIndex");
	//说明没配置文件啊.
	if (AdapterIndex==-1)
	{
		//啥也不做..
	}else{
		cnet.SetAdapterIndex(AdapterIndex);
	}



	//配置文件读窗体xy
	int last_x=IniGetInt(FilePath,"window","pos_x");
	int last_y=IniGetInt(FilePath,"window","pos_y");
	 
	
	CString bgimg=IniGetString(FilePath,"window","bkimg");


	//窗体的背景图
	HBITMAP hBitmap;// = m_Logo.GetBitmap();
	//加载指定bmp,使用bmp默认宽高
	hBitmap = (HBITMAP)::LoadImage(NULL,bgimg,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	if(hBitmap==NULL)
	{
		//AfxMessageBox("er");
		//从配置文件载入失败,从exe的默认资源加载
		hBitmap  = ::LoadBitmap (::GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1)) ;;// m_Logo.GetBitmap();
	}

	m_Bitmap.Attach(hBitmap);
	  
	GetBITMAPInfo(m_Bitmap,width,height);

 
	//窗体移动xy并缩放
	MoveWindow(last_x,last_y, width,  height );
	//static控件移动并缩放
	//m_Logo.MoveWindow(last_x,last_y, width , height);

	//无配置文件.所以就居中吧
	if (last_x==-1 && last_y==-1 )
	{
		CenterWindow();
	}
	 
	//top级窗口
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

  
	
	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	
	//需要的gdi字体
	CreateFont();
 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//实现鼠标左键按下拖拉窗体
UINT CFloatWnd::OnNcHitTest(CPoint pt)
{
	UINT nHitTest = CDialog::OnNcHitTest(pt);


	//鼠标在x关闭按钮区域
	//if (mouseOnCloseBtnRect())
	//{
	//	return nHitTest;
	//}


	//HTCLIENT  表示客户区被点击了,下面的hack方法是让鼠标点击窗体区域事件都被修改成点击标题栏的事件,从而实现拖拉窗体,所以一切鼠标事件处理要在上面检查完
	if (nHitTest == HTCLIENT &&
				::GetAsyncKeyState(MK_LBUTTON) < 0) // 如果鼠标左键按下，GetAsyncKeyState函数的返回值小于0

		nHitTest = HTCAPTION;

	return nHitTest;
}


void CFloatWnd::OnOK()
{
	// TODO: Add extra cleanup here

	//OnOK();
}

void CFloatWnd::OnCancel() 
{
	// TODO: Add extra cleanup here

	//	CDialog::OnCancel();
}

//右键弹起.弹出菜单
void CFloatWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu m_Right;
	m_Right.LoadMenu(IDR_MENU1);
	CMenu *pSub = m_Right.GetSubMenu(0);

	ClientToScreen(&point);
	pSub->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this,NULL);
	
	CDialog::OnRButtonUp(nFlags, point);
}

//退出菜单
void CFloatWnd::OnExit() 
{

	CRect rect;
	this->GetWindowRect(&rect);	//得到窗体坐标
	CString msg;


	msg.Format("%d",rect.left);
	WritePrivateProfileString ("window","pos_x", msg  ,  FilePath); 
	
	msg.Format("%d",rect.top);
	WritePrivateProfileString ("window","pos_y", msg ,  FilePath); 


	msg.Format("%d", cnet.GetCurrAdapterIndex() );
	WritePrivateProfileString ("network","AdapterIndex", msg ,  FilePath); 


	// TODO: Add your command handler code here
	//通知父窗体退出
	CWnd *pParent = GetParent();
	ASSERT(pParent);

	pParent->PostMessage(WM_QUIT,0,0);
}

#include "../NetWorkAdapterSetDlg.h"
#include ".\floatwnd.h"
void CFloatWnd::OnShow() 
{
	CNetWorkAdapterSetDlg dlg;
	dlg.DoModal();

}

//0-255
void CFloatWnd::OnUpdateTransparent(int iTransparent)
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
					
			pFun(m_hWnd,RGB(255,0,255),iTransparent,1|2);//ULW_COLORKEY 1表示要用透明色把指定色不显示,LWA_ALPHA 2表示要控制半透明
		}
		FreeLibrary(hInst); 
	}
}

void CFloatWnd::OnNcLButtonDblClk(UINT nFlags, CPoint point) 
{
 
	// TODO: Add your message handler code here and/or call default	
	//CWnd *pParent = GetParent();
	//ASSERT(pParent);
 //
	//if(!pParent->IsWindowVisible())
	//{
 // 
	////	pParent->ShowWindow(SW_SHOW);
	////	pParent->SetForegroundWindow();
	//}else{
	//	pParent->ShowWindow(SW_HIDE);
	//	 
	//}
	// 

	CDialog::OnNcLButtonDblClk(nFlags, point);
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

//在begin和end之间来回的函数
float RandNum(float  begin,float end,float vlaue)
{
	static float yrot=begin;
	static bool a=true;
	if(a==true)  yrot+=vlaue;
	if(a==false) yrot-=vlaue;
	if(yrot>=end) 
	{
		a=false;
	}
	else if(yrot<=begin)
	{
		a=true;
	}
	printf("%3.1f\r",yrot);
	return yrot;
} 


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

/*
void TextOutToHDC(HDC hdc,int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor)
{
	//创建兼容设备的内存dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//内存dc选择位图
	SelectObject(hdcMem,m_hFont);

	SIZE size;
	// 获取字符位图大小 
	::GetTextExtentPoint32(hdcMem, msg, strlen(msg), &size);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdcMem,size.cx, size.cy);

	HGDIOBJ hOldBmp=SelectObject(hdcMem,hBitmap);

	SetBkColor(hdcMem, RGB(0,0,0));//黑色背景
	SetTextColor(hdcMem, fontColor );      //字体颜色 

	SetBkMode(hdcMem, OPAQUE);                     //用当前的背景颜色填充背景
	//SetBkMode(hdcMem,TRANSPARENT);

	TextOut(hdcMem,x, y, msg, strlen(msg));	  // 输出文字到暂存hDC 

	//恢复原来的内存dc设备
	hBitmap = (HBITMAP)SelectObject(hdcMem, hOldBmp);

	//内存dc选择位图
	SelectObject(hdcMem,hBitmap);
	BitBlt(hdc, x, y,
		size.cx,size.cy,  //bmp宽高
		hdcMem, 0,0,  //hdcMem的xy,所以这里从左上角复制图片到内存dc
		SRCCOPY); //把屏幕图象copy



	//删除内存dc
	DeleteDC(hdcMem);


	DeleteObject(hBitmap);
}
*/


HBITMAP TextOutToBMP(int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor )
{
	//创建兼容设备的内存dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//内存dc选择位图
	 SelectObject(hdcMem,m_hFont);

	SIZE size;
	/** 获取字符位图大小 */
	::GetTextExtentPoint32(hdcMem, msg, strlen(msg), &size);
	
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcMem,size.cx, size.cy);

	HGDIOBJ hOldBmp=SelectObject(hdcMem,hBitmap);
	
	SetBkColor(hdcMem, RGB(0,0,0));//黑色背景
	SetTextColor(hdcMem, fontColor );      /**< 字体颜色 */

	SetBkMode(hdcMem, OPAQUE);                     /**< 用当前的背景颜色填充背景 */
	SetBkMode(hdcMem,TRANSPARENT);

	TextOut(hdcMem,x, y, msg, strlen(msg));	   /**< 输出文字到暂存hDC */

	//恢复原来的内存dc设备
	hBitmap = (HBITMAP)SelectObject(hdcMem, hOldBmp);

	//删除内存dc
	DeleteDC(hdcMem);

	return hBitmap;
}

void CBitmapToHDC(HDC hdc,CBitmap& hbmp,int pic_x,int pic_y)
{
	int nX;  
	int nY;
	GetBITMAPInfo(hbmp,nX,nY);

	//创建兼容设备的内存dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//内存dc选择位图
	SelectObject(hdcMem,hbmp);

	BitBlt(hdc,
		pic_x, pic_y, //指定hdc左上角
		nX,nY,  //bmp宽高
		hdcMem, 
		0,0,  //hdcMem的xy,所以这里从左上角复制图片到内存dc
		SRCCOPY); //把屏幕图象copy
	//删除内存dc
	DeleteDC(hdcMem);
}

BYTE r=255;
BYTE g=255;
BYTE b=255;

void CFloatWnd::Paint()
{

	int nX;  
	int nY;
	GetBITMAPInfo(m_Bitmap,nX,nY);


	HDC hdc;  //声明一个设备上下文handle
	hdc=::GetDC(m_hWnd);  //得到handle


	//绘制背景图片
	CBitmapToHDC(hdc,m_Bitmap,0,0);

	//g=255;//RandNum(150,250,3);
	//g=230;
	//b=255;//(abs(g-50)<50?(b+5):abs(g-50)) ;

	//输出字
	TextOutToHDC(hdc,
		10,  //字输出的x坐标
		nY/2/2, //字输出的y坐标
		msg,m_hFont,RGB(r,g,b));


	//SelectObject(hdc,h);
	::ReleaseDC(m_hWnd,hdc); //释放hdc
}

void CFloatWnd::OnPaint()
{
	 
	CDialog::OnPaint();
	
	Paint();

 
 
}

void CFloatWnd::SetMsg(char* d)
{
	strcpy(msg,d);
	 
	Paint();
//	Invalidate(1);
}

void CFloatWnd::SetToolTipText(char* m)
{
	m_openToolTip.UpdateTipText(m,this);
}

 
//鼠标在关闭按钮区域?
bool CFloatWnd::mouseOnCloseBtnRect()
{
	/*
	CRect   rect;   
	GetWindowRect(&rect);

	//得到相对坐标
	POINT   pt2; 
	GetCursorPos(&pt2);  //得到鼠标绝对坐标并保存在pt中

	BITMAP bmp;
	m_CloseBitmap.GetBitmap(&bmp);
	rect.left=rect.right-bmp.bmWidth;
	rect.bottom=rect.top+bmp.bmHeight;

	//鼠标在x按钮矩形区域?
	return rect.PtInRect(pt2);;
	*/
	return 0;
}

//鼠标左键弹起
void CFloatWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	 ////按下x关闭
	 //if (mouseOnCloseBtnRect())
	 //{
		//// OnExit();
	 //}

	CDialog::OnLButtonUp(nFlags, point);
}

#include "../caboutdlg.h"

//关于作者
void CFloatWnd::On32776()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}
