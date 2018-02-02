// NetDrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "networkmonitor.h"
#include "NetDrawDlg.h"
#include ".\netdrawdlg.h"


// CNetDrawDlg �Ի���

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
		//ȡ��SetLayeredWindowAttributes����ָ�� 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			//SetLayeredWindowAttributes( RGB(255,0,255),iTransparent,ULW_COLORKEY|LWA_ALPHA);//LWA_ALPHA
			//RGB(255,0,255)

			pFun(hWnd,RGB(255,0,255),iTransparent,1|2);//ULW_COLORKEY 1��ʾҪ��͸��ɫ��ָ��ɫ����ʾ,LWA_ALPHA 2��ʾҪ���ư�͸��
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
	
	//�����ļ�������xy
	int last_x=IniGetInt(FilePath,"window","pos2_x",0);
	int last_y=IniGetInt(FilePath,"window","pos2_y",0);
	 
	

	//����ı���ͼ //����ָ��bmp,ʹ��bmpĬ�Ͽ��
 	hBitmap = NULL;// (HBITMAP)::LoadImage(NULL, "res//logo2.bmp" ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	if(hBitmap==NULL)
	{
		//AfxMessageBox("er");
		//�������ļ�����ʧ��,��exe��Ĭ����Դ����
		//hBitmap  = ::LoadBitmap (::GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP2)) ;;// m_Logo.GetBitmap();
	}
 

	//�õ�bmp���
	//GetBITMAPInfo(hBitmap,m_width,m_height);
	m_width=IniGetInt(FilePath,"window","width",300);
	m_height=IniGetInt(FilePath,"window","height",200);


	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	up_R=IniGetInt(FilePath,"window","up_R",0);
	up_G=IniGetInt(FilePath,"window","up_G",255);
	up_B=IniGetInt(FilePath,"window","up_B",0);

	m_up.SetColor(RGB(up_R,up_G,up_B));

	download_R=IniGetInt(FilePath,"window","download_R",255);
	download_G=IniGetInt(FilePath,"window","download_G",0);
	download_B=IniGetInt(FilePath,"window","download_B",0); 

	m_download.SetColor(RGB(download_R,download_G,download_B));

	height=IniGetInt(FilePath,"window","height1024kb",32);

    int Transparent=IniGetInt(FilePath,"window","Transparent2",255);

	//����WS_EX_LAYERED��չ����
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong( GetSafeHwnd() ,GWL_EXSTYLE)^0x80000);

 
	// ʹ���ڳ��Ӷ���
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,	SWP_NOSIZE|SWP_NOMOVE);
	//ȥ������
	//RemoveWndTitleStyle(this->GetSafeHwnd());

 
 
		//����͸����
		OnUpdateTransparent(GetSafeHwnd(), Transparent);
	 
	 

  

	//�����ƶ�xy��,���ų�bmp��С
	MoveWindow(last_x,last_y, m_width+2, m_height+2,TRUE );
 

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CNetDrawDlg::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y)
{
 
	//���������豸���ڴ�dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//�ڴ�dcѡ��λͼ
	SelectObject(hdcMem,hbmp);

	BitBlt(hdc,
		pic_x, pic_y, //ָ��hdc���Ͻ�
		m_width,m_height,  //bmp���
		hdcMem, 
		0,0,  //hdcMem��xy,������������ϽǸ���ͼƬ���ڴ�dc
		SRCCOPY); //����Ļͼ��copy
	//ɾ���ڴ�dc
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
	//��ɫ����
 
 	CBrush mybrush1;   //����ˢ��
	mybrush1.CreateSolidBrush(RGB(0,0,0)); //����ˢ��
 
	pDC->FillRect(rect,&mybrush1);//��ʼˢ
 

	//---------------------------------------------------
 
	CPen pen(0,1,RGB(34,120,80)); 
	pDC->SelectObject(pen);

	//����y�̶�
	pDC->MoveTo(0, rect.top);//���
	pDC->LineTo(0,rect.bottom);

	rect.right-=3;

	//����x�̶�
	pDC->MoveTo(1,rect.bottom);//���
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


	//��������
	m_download.Draw( rect ,pDC ,height);

	//�ϴ�����
	m_up.Draw( rect,pDC,height );


	ReleaseDC(pDC);
}

// CNetDrawDlg ��Ϣ�������
 

 