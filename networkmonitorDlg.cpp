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


// networkmonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "networkmonitor.h"
#include "networkmonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include ".\networkmonitordlg.h"


#include "NetStat.h"

CNetStat cnet;
 

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
 
CnetworkmonitorDlg::CnetworkmonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CnetworkmonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnetworkmonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CnetworkmonitorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_SELECT, OnShow)
	ON_COMMAND(ID_32776, On32776)

	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

#include "caboutdlg.h"
//关于作者
void CnetworkmonitorDlg::On32776()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}

// CnetworkmonitorDlg 消息处理程序
BOOL CnetworkmonitorDlg::PreTranslateMessage(MSG* pMsg) 
{ 
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message) 
	{ 
	case WM_LBUTTONDOWN: 
	case WM_LBUTTONUP: 
	case WM_MOUSEMOVE: 
		m_openToolTip.RelayEvent(pMsg); 

		break;

	case WM_LBUTTONDBLCLK:
		if (m_drawDlg.IsWindowVisible())
		{
			m_drawDlg.ShowWindow(SW_HIDE);
		}else{
			m_drawDlg.ShowWindow(SW_SHOW);
		}
		 
		
		break;
	} 

	UINT rt= m_floatWnd.MsgProc(pMsg->hwnd,pMsg->message,pMsg->wParam,pMsg->lParam);
	if (rt!=FALSE)
	{
		return rt;
	}

 
	return CDialog::PreTranslateMessage(pMsg);
} 

BOOL CnetworkmonitorDlg::OnInitDialog()
{
	 
	


	CDialog::OnInitDialog();


	  TipTextColorR=IniGetInt(FilePath,"window","TipTextColorR",0);
	  TipTextColorG=IniGetInt(FilePath,"window","TipTextColorG",0);
	  TipTextColorB=IniGetInt(FilePath,"window","TipTextColorB",255);


	m_openToolTip.Create(this);  
	m_openToolTip.AddTool( this , "" ); 
	m_openToolTip.SetDelayTime(200); 
	m_openToolTip.SetTipTextColor( RGB(TipTextColorR,TipTextColorG,TipTextColorB) ); 
	m_openToolTip.SetTipBkColor( RGB(255,255,255)); 
	m_openToolTip.Activate(TRUE); 
	m_openToolTip.SetMaxTipWidth(250);  

		 
	m_drawDlg.Create(IDD_NETDRAWDLG,this);//创建非模态对话框
	m_drawDlg.ShowWindow(SW_HIDE); 


	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
 
	//pFloatWnd = new CFloatWnd( );


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
	if (last_x==-1 || last_y==-1)
	{
		last_x=0;
		last_y=0;
	}

	m_floatWnd.Init(GetSafeHwnd(),last_x,last_y);
	m_floatWnd.SetMsg("初始化中");


	//无配置文件.所以就居中吧
	if (last_x==0 && last_y==0 )
	{
		CenterWindow();
	}


 
	

	//CFloatWnd*	pFloatWnd = new CFloatWnd( );
 
	SetTimer(0,2000,0);//流量统计

//	SetTimer(1,20,0);//隐藏窗体的timer,只用一次.然后kill

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
} 

void CnetworkmonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	//	CAboutDlg dlgAbout;
	//	dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CnetworkmonitorDlg::OnPaint() 
{
 

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		 
		CDialog::OnPaint( );
	}

	 	HDC hdc=::GetDC(m_hWnd);  //得到handle
			
		m_floatWnd.Paint( hdc );

		::ReleaseDC(m_hWnd,hdc); //释放hdc
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CnetworkmonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//右键弹起.弹出菜单
void CnetworkmonitorDlg::OnRButtonUp(UINT nFlags, CPoint point) 
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
void CnetworkmonitorDlg::OnExit() 
{

	CRect rect;
	this->GetWindowRect(&rect);	//得到窗体坐标
	CString msg;


	msg.Format("%d",rect.left);
	WritePrivateProfileString ("window","pos_x", msg  ,  FilePath); 

	msg.Format("%d",rect.top);
	WritePrivateProfileString ("window","pos_y", msg ,  FilePath); 

		
	m_drawDlg.GetWindowRect(&rect);	//得到窗体坐标

	msg.Format("%d",rect.left);
	WritePrivateProfileString ("window","pos2_x", msg  ,  FilePath); 

	msg.Format("%d",rect.top);
	WritePrivateProfileString ("window","pos2_y", msg ,  FilePath); 


	msg.Format("%d", cnet.GetCurrAdapterIndex() );
	WritePrivateProfileString ("network","AdapterIndex", msg ,  FilePath); 


	msg.Format("%d", TipTextColorR );
	WritePrivateProfileString ("window","TipTextColorR", msg ,  FilePath); 

	msg.Format("%d", TipTextColorG );
	WritePrivateProfileString ("window","TipTextColorG", msg ,  FilePath); 

	msg.Format("%d", TipTextColorB );
	WritePrivateProfileString ("window","TipTextColorB", msg ,  FilePath); 
 

	msg.Format("%d", m_drawDlg.height );
	WritePrivateProfileString ("window","height128kb", msg ,  FilePath); 
	msg.Format("%d", m_drawDlg.m_width );
	WritePrivateProfileString ("window","width", msg ,  FilePath); 
	msg.Format("%d", m_drawDlg.m_height );
	WritePrivateProfileString ("window","height", msg ,  FilePath); 
 


	msg.Format("%d", m_drawDlg.up_R );
	WritePrivateProfileString ("window","up_R", msg ,  FilePath); 
	msg.Format("%d", m_drawDlg.up_G );
	WritePrivateProfileString ("window","up_G", msg ,  FilePath); 
	msg.Format("%d", m_drawDlg.up_B );
	WritePrivateProfileString ("window","up_B", msg ,  FilePath); 

	msg.Format("%d", m_drawDlg.download_R );
	WritePrivateProfileString ("window","download_R", msg ,  FilePath); 
	msg.Format("%d", m_drawDlg.download_G );
	WritePrivateProfileString ("window","download_G", msg ,  FilePath); 
	msg.Format("%d", m_drawDlg.download_B );
	WritePrivateProfileString ("window","download_B", msg ,  FilePath); 



	// TODO: Add your command handler code here
	//通知父窗体退出
//	CWnd *pParent = GetParent();
//	ASSERT(pParent);

	PostMessage(WM_QUIT,0,0);
}

#include "NetWorkAdapterSetDlg.h"
 
void CnetworkmonitorDlg::OnShow() 
{
	CNetWorkAdapterSetDlg dlg;
	dlg.DoModal();

}

//文件大小格式化
void FileSize_Format(DWORD dwBytes,char* msg)
{
	
	if(dwBytes<1024)//如果文件小于1024字节,就用B显示
	{
		sprintf(msg,"%3d B",dwBytes);

	}else if(dwBytes<1024*1024)//如果文件小于1M就用KB显示
	{
		sprintf(msg,"%3.1f KB",(float)dwBytes/1024); 

	}else //超过1M了,
	{
		sprintf(msg,"%3.2f MB",(float)dwBytes/1024/1024);

	}
}


void Speed_Format(DWORD dwBytes,char* msg)
{
	dwBytes/=2;

	if(dwBytes<1024)//如果文件小于1024字节,就用B显示
	{
		sprintf(msg,"%3d B/s ",dwBytes);

	}else if(dwBytes<1024*1024)//如果文件小于1M就用KB显示
	{
		sprintf(msg,"%3.0f KB/s",(float)dwBytes/1024); 

	}else //超过1M了,
	{
		sprintf(msg,"%3.2f MB/s",(float)dwBytes/1024/1024);

	}
}

BOOL g_bFirstCheck=TRUE;

DWORD lastinbytes=0;
DWORD lastoutbytes=0; 

void CnetworkmonitorDlg::Check()
{

	DWORD in_bytes=0;
	DWORD out_bytes=0;
	cnet.getNetworkStatus(in_bytes,out_bytes);

	DWORD in_speed;//下行
	DWORD out_speed;//上行
	in_speed= in_bytes - lastinbytes  ;
 
	lastinbytes=in_bytes;

	out_speed= out_bytes - lastoutbytes  ;
 
	lastoutbytes=out_bytes;



	char msg[321];
	char msg1[321];
	FileSize_Format(out_bytes,msg1);
	char msg2[321];
	FileSize_Format(in_bytes,msg2);

	char msg_s1[321],msg_s2[321];
	Speed_Format(in_speed,msg_s1);
	Speed_Format(out_speed,msg_s2);

	if (g_bFirstCheck)
	{
		g_bFirstCheck=FALSE;

		m_floatWnd.SetMsg( "下行[ 0 B/s ] 上行[ 0 B/s ]" );
		
		return;
	}
	sprintf(msg,"下行[%s] 上行[%s]" ,msg_s1,msg_s2 );
	m_floatWnd.SetMsg(msg);


	char msgtot[255];
	sprintf(msgtot,"下载[%s]  上传[%s] " , msg2  , msg1);
	
	m_openToolTip.UpdateTipText(msgtot,this);


	m_drawDlg.m_download.list_adddata(in_speed/1024/2); //字节转kb 由于统计了2秒的速度 所以要除以2
	m_drawDlg.m_up.list_adddata(out_speed/1024/2);
	m_drawDlg.Draw();

	//SetWindowText(msg);
}

void CnetworkmonitorDlg::OnBnClickedOk()
{
	 Check();
}
 
void CnetworkmonitorDlg::OnTimer(UINT nIDEvent)
{
	  
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Check();

	CDialog::OnTimer(nIDEvent);
}

void CnetworkmonitorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

 
	// TODO: 在此处添加消息处理程序代码
}
