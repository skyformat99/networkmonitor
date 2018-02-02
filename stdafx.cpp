// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// networkmonitor.pch ����Ԥ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"




char FilePath[255]=".\\config.ini"; 

// ������
int IniGetInt(  char *strFile, char *lpAppName, char *lpKeyName )
{
	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //��
	if(ret==0){
		//MessageBox(0,"ini��intʧ��!","",0);
		return -1;
	}else{
		ret=atoi(inBuf);
		return ret;
	}

}

int IniGetInt(  char *strFile, char *lpAppName, char *lpKeyName ,int default_v)
{
	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //��
	if(ret==0){
		//MessageBox(0,"ini��intʧ��!","",0);
		return default_v;
	}else{
		ret=atoi(inBuf);
		return ret;
	}

}

CString IniGetString(  char *strFile, char *lpAppName, char *lpKeyName )
{
	CString str;

	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //��
	if(ret==0)
	{
		//MessageBox(0,"ini��intʧ��!","",0);
	}else{
		str=inBuf; 
	}

	return str;
}