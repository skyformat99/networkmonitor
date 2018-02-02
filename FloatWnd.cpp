#include "StdAfx.h"
#include ".\floatwnd.h"
#include "resource.h"

void TextOutToHDC(HDC hdc,int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor)
{
	//�ڴ�dcѡ��λͼ
	HGDIOBJ h=SelectObject(hdc,m_hFont);

	SetBkColor(hdc, RGB(0,0,0));//��ɫ����
	SetTextColor(hdc, fontColor );      /**< ������ɫ */

	//SetBkMode(hdc, OPAQUE);                     /**< �õ�ǰ�ı�����ɫ��䱳�� */
	SetBkMode(hdc,TRANSPARENT);

	TextOut(hdc,x, y, msg, strlen(msg));	   /**< ������ֵ��ݴ�hDC */

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

//ȥ������ı��������
void CFloatWnd::RemoveWndTitleStyle(HWND hWnd)
{
	long   dwStyle   =   GetWindowLong(hWnd,   GWL_STYLE); 
	dwStyle   &=   ~(WS_CAPTION); 

	SetWindowLong(hWnd,   GWL_STYLE,   dwStyle); 
}

// ����ı��������
void CFloatWnd::AddWndTitleStyle(HWND hWnd)
{
	long   dwStyle   =   GetWindowLong(hWnd,   GWL_STYLE); 
	dwStyle   |=  (WS_CAPTION); 

	SetWindowLong(hWnd,   GWL_STYLE,   dwStyle); 
}

void CFloatWnd::CreateFont()
{
	/** �������� */
	m_hFont = ::CreateFont(12,   /**< ����߶� */
		0,						/**< ������ */
		0,						/**< �������ת�Ƕ�  */
		0,						/**< ������ߵ���ת�Ƕ� */
		FW_NORMAL,				/**< ��������� */
		FALSE,					/**< �Ƿ�ʹ��б�� */
		FALSE,					/**< �Ƿ�ʹ���»��� */
		FALSE,					/**< �Ƿ�ʹ��ɾ���� */
		GB2312_CHARSET,			/**< �����ַ��� */
		OUT_TT_PRECIS,			/**< ������� */
		CLIP_DEFAULT_PRECIS,	/**< �ü����� */
		ANTIALIASED_QUALITY,	/**< ������� */
		FF_DONTCARE|DEFAULT_PITCH,		/**< Family And Pitch */
		"����");				/**< �������� */

}

void CFloatWnd::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y)
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

 
void CFloatWnd::Init(HWND hDlg,int x,int y)
{
	this->m_hDlg=hDlg;

	// ʹ���ڳ��Ӷ���
	::SetWindowPos(hDlg,HWND_TOPMOST,0,0,0,0,	SWP_NOSIZE|SWP_NOMOVE);

	//����WS_EX_LAYERED��չ����
	SetWindowLong(hDlg,GWL_EXSTYLE,GetWindowLong( hDlg ,GWL_EXSTYLE)^0x80000);

	//ȥ������
	RemoveWndTitleStyle(hDlg);
	//AddWndTitleStyle(hDlg);

 
	CString bgimg=IniGetString(FilePath,"window","bkimg");
    int Transparent=IniGetInt(FilePath,"window","Transparent",255);
  
	//����ı���ͼ //����ָ��bmp,ʹ��bmpĬ�Ͽ��
	hBitmap = (HBITMAP)::LoadImage(NULL, bgimg ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	if(hBitmap==NULL)
	{
		//AfxMessageBox("er");
		//�������ļ�����ʧ��,��exe��Ĭ����Դ����
		hBitmap  = ::LoadBitmap (::GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1)) ;;// m_Logo.GetBitmap();
	}


	//�õ�bmp���
	GetBITMAPInfo(hBitmap,m_width,m_height);

	//�����ƶ�xy��,���ų�bmp��С
	MoveWindow(hDlg,x,y, m_width,  m_height,TRUE );

	 
    //����͸����
    OnUpdateTransparent(hDlg, Transparent );
 
	 

	//��������
	CreateFont();

}

BYTE r=255;
BYTE g=255;
BYTE b=255;
void CFloatWnd::Paint(HDC hdc)
{
//	HDC hdc=::GetDC(hDlg);  //�õ�handle

	//���Ʊ���ͼƬ
	CBitmapToHDC(hdc,hBitmap,0,0);

	//�����
	TextOutToHDC(hdc,
		10,  //�������x����
		m_height/2/2, //�������y����
		msg,m_hFont,RGB(r,g,b));

//	::ReleaseDC(hDlg,hdc); //�ͷ�hdc
}

void CFloatWnd::SetMsg(char* d)
{
	strcpy(msg,d);

	HDC hdc=::GetDC(m_hDlg);  //�õ�handle
	
	Paint(hdc);
	//	Invalidate(1);
		
	::ReleaseDC(m_hDlg,hdc); //�ͷ�hdc
}
 

UINT   CFloatWnd::MsgProc(HWND hDlg, //�Ի�����
						  UINT message, //��Ϣ����
						  WPARAM wParam, //��Ϣ������Ϣ
						  LPARAM lParam) //��Ϣ������Ϣ
{
	switch(message) // ��Ϣ����
	{
/*	case WM_CREATE:
	case WM_INITDIALOG: //�Ի����ʼ����Ϣ
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
	return(FALSE); //����û�д������Ϣ,����FALSE
}
