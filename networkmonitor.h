// networkmonitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CnetworkmonitorApp:
// �йش����ʵ�֣������ networkmonitor.cpp
//

class CnetworkmonitorApp : public CWinApp
{
public:
	CnetworkmonitorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CnetworkmonitorApp theApp;
