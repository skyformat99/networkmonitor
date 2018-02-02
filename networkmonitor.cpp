// networkmonitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "networkmonitor.h"
#include "networkmonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnetworkmonitorApp

BEGIN_MESSAGE_MAP(CnetworkmonitorApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CnetworkmonitorApp ����

CnetworkmonitorApp::CnetworkmonitorApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

 

}


// Ψһ��һ�� CnetworkmonitorApp ����

CnetworkmonitorApp theApp;


// CnetworkmonitorApp ��ʼ��

BOOL CnetworkmonitorApp::InitInstance()
{
	//exe�����Ŷδ����.ֻ������һ��ʵ��
	HANDLE g_hMap = CreateFileMapping(0, NULL, PAGE_READWRITE, 0, 1024, "MHOnline Client Application");
	if(g_hMap != NULL && GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		CloseHandle(g_hMap); 
		g_hMap = NULL;
		return FALSE;
	}



	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CnetworkmonitorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
