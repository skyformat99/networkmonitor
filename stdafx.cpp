// stdafx.cpp : 只包括标准包含文件的源文件
// networkmonitor.pch 将是预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"




char FilePath[255]=".\\config.ini"; 

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

int IniGetInt(  char *strFile, char *lpAppName, char *lpKeyName ,int default_v)
{
	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //读
	if(ret==0){
		//MessageBox(0,"ini读int失败!","",0);
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
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //读
	if(ret==0)
	{
		//MessageBox(0,"ini读int失败!","",0);
	}else{
		str=inBuf; 
	}

	return str;
}