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