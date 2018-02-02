// networkmonitorDlg.cpp : ʵ���ļ�
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
 

#define HOTKEY_ID 9999


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
 
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
//��������
void CnetworkmonitorDlg::On32776()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
	dlg.DoModal();
}


int CnetworkmonitorDlg::OnHOTKEY()
{
	//ע�� ��
	::system("shutdown -l");
	return 1;
}

// CnetworkmonitorDlg ��Ϣ�������
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

		 
	m_drawDlg.Create(IDD_NETDRAWDLG,this);//������ģ̬�Ի���
	m_drawDlg.ShowWindow(SW_HIDE); 


	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
 
	//pFloatWnd = new CFloatWnd( );


	//�����ļ���ָ������index
	int AdapterIndex=IniGetInt(FilePath,"network","AdapterIndex");
	//˵��û�����ļ���.
	if (AdapterIndex==-1)
	{
		//ɶҲ����..
	}else{
		cnet.SetAdapterIndex(AdapterIndex);
	}
 
	//�����ļ�������xy
	int last_x=IniGetInt(FilePath,"window","pos_x");
	int last_y=IniGetInt(FilePath,"window","pos_y");
	if (last_x==-1 || last_y==-1)
	{
		last_x=0;
		last_y=0;
	}

	m_floatWnd.Init(GetSafeHwnd(),last_x,last_y);
	m_floatWnd.SetMsg("��ʼ����");


	//�������ļ�.���Ծ;��а�
	if (last_x==0 && last_y==0 )
	{
		CenterWindow();
	}


 
	
	int ret=::RegisterHotKey(m_hWnd, //  hWnd�������ȼ�����WM_HOTKEY��Ϣ�Ĵ��ھ�������ò���NULL�����ݸ������̵߳�WM_HOTKEY��Ϣ��������Ϣѭ�����н��д���
	   HOTKEY_ID,  //�����ȼ��ı�ʶ���������߳��е������ȼ�����ʹ��ͬ���ı�ʶ����Ӧ�ù��ܳ�����붨��һ��0X0000-0xBFFF��Χ��ֵ��һ������Ķ�̬���ӿ⣨DLL�����붨��һ��0xC000-0xFFFF��Χ��ֵ��GlobalAddAtom�������ظ÷�Χ����Ϊ�˱�����������̬���ӿⶨ����ȼ���ͻ��һ��DLL����ʹ��GlobalAddAtom��������ȼ��ı�ʶ����
	   MOD_CONTROL   |   MOD_SHIFT,
	   
		'L');       //ע��   ctrl   +   shift   +   L   
	if(ret==0)
	{
		::AfxMessageBox("ע���ȼ�ʧ�ܣ�");
	}


	//CFloatWnd*	pFloatWnd = new CFloatWnd( );
 
	SetTimer(0,2000,0);//����ͳ��

//	SetTimer(1,20,0);//���ش����timer,ֻ��һ��.Ȼ��kill



	//д��ע���,����������
	HKEY hKey; //�ҵ�ϵͳ�������� 
	LPCTSTR lpRun = "Software\\Microsoft\\Windows\\CurrentVersion\\Run"; 
	//��������Key 
	long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_WRITE, &hKey);
	if(lRet == ERROR_SUCCESS)
	{   
		char pFileName[MAX_PATH] = {0};  
		//�õ����������ȫ·��  
		DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH);  
		//���һ����Key,������ֵ 
		// �����"getip"��Ӧ�ó������֣����Ӻ�׺.exe�� 
		lRet = RegSetValueEx(hKey, "networkmonitor", 0, REG_SZ, (BYTE *)pFileName, dwRet);

		//�ر�ע��� 
		RegCloseKey(hKey);  
		if(lRet != ERROR_SUCCESS)     
		{   
			AfxMessageBox("ϵͳ��������,������ϵͳ����");   
		}
	}

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
} 

LRESULT   CnetworkmonitorDlg::WindowProc(UINT   message,   WPARAM   wParam,   LPARAM   lParam)     
{   
	//   TODO:   Add   your   specialized   code   here   and/or   call   the   base   class   
	if   (message==WM_HOTKEY)   
	{   
		if   (wParam==HOTKEY_ID)   
		{   
			   
						return OnHOTKEY();
				 
		}   

	}   
	return   CDialog::WindowProc(message,   wParam,   lParam);   
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CnetworkmonitorDlg::OnPaint() 
{
 

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		 
		CDialog::OnPaint( );
	}

	 	HDC hdc=::GetDC(m_hWnd);  //�õ�handle
			
		m_floatWnd.Paint( hdc );

		::ReleaseDC(m_hWnd,hdc); //�ͷ�hdc
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CnetworkmonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//�Ҽ�����.�����˵�
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

//�˳��˵�
void CnetworkmonitorDlg::OnExit() 
{

	CRect rect;
	this->GetWindowRect(&rect);	//�õ���������
	CString msg;


	msg.Format("%d",rect.left);
	WritePrivateProfileString ("window","pos_x", msg  ,  FilePath); 

	msg.Format("%d",rect.top);
	WritePrivateProfileString ("window","pos_y", msg ,  FilePath); 

		
	m_drawDlg.GetWindowRect(&rect);	//�õ���������

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



		//�ȼ�ɾ��
	UnregisterHotKey(m_hWnd,HOTKEY_ID);   ////   

	// TODO: Add your command handler code here
	//֪ͨ�������˳�
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

//�ļ���С��ʽ��
void FileSize_Format(DWORD dwBytes,char* msg)
{
	
	if(dwBytes<1024)//����ļ�С��1024�ֽ�,����B��ʾ
	{
		sprintf(msg,"%3d B",dwBytes);

	}else if(dwBytes<1024*1024)//����ļ�С��1M����KB��ʾ
	{
		sprintf(msg,"%3.1f KB",(float)dwBytes/1024); 

	}else //����1M��,
	{
		sprintf(msg,"%3.2f MB",(float)dwBytes/1024/1024);

	}
}


void Speed_Format(DWORD dwBytes,char* msg)
{
	dwBytes/=2;

	if(dwBytes<1024)//����ļ�С��1024�ֽ�,����B��ʾ
	{
		sprintf(msg,"%3d B/s ",dwBytes);

	}else if(dwBytes<1024*1024)//����ļ�С��1M����KB��ʾ
	{
		sprintf(msg,"%3.0f KB/s",(float)dwBytes/1024); 

	}else //����1M��,
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

	DWORD in_speed;//����
	DWORD out_speed;//����
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

		m_floatWnd.SetMsg( "����[ 0 B/s ] ����[ 0 B/s ]" );
		
		return;
	}
	sprintf(msg,"����[%s] ����[%s]" ,msg_s1,msg_s2 );
	m_floatWnd.SetMsg(msg);


	char msgtot[255];
	sprintf(msgtot,"����[%s]  �ϴ�[%s] " , msg2  , msg1);
	
	m_openToolTip.UpdateTipText(msgtot,this);


	m_drawDlg.m_download.list_adddata(in_speed/1024/2); //�ֽ�תkb ����ͳ����2����ٶ� ����Ҫ����2
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
	  
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Check();

	CDialog::OnTimer(nIDEvent);
}

void CnetworkmonitorDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

 
	// TODO: �ڴ˴������Ϣ����������
}
