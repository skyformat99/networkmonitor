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



#pragma once

#include <iphlpapi.h>
#pragma comment(lib,"IPHlpApi.Lib")


/************************************************************************/
/* 

获得本机网卡信息,以及对应网卡的流量数据

*/
/************************************************************************/
class CNetStat
{
	 

	int currAdapterIndex;//指定当前网卡,用于获取

public:
	PIP_INTERFACE_INFO pInfo;//网卡信息

	int GetCurrAdapterIndex(){return currAdapterIndex;};

	CNetStat(void)
	{
	  pInfo=NULL;
		
	  EnumAdapter();
	}
	~CNetStat(void)
	{
	  if (pInfo)
	  {
		  delete pInfo;
		  pInfo=NULL;
	  }
	}
	
	//设置要监视的网卡的索引
	void SetAdapterIndex(int idx)
	{
		currAdapterIndex=idx;
	}

	bool EnumAdapter()
	{
		if (pInfo)
		{
			delete pInfo;
			pInfo=NULL;
		}
		// Declare and initialize variables
		
		pInfo = (IP_INTERFACE_INFO *) malloc( sizeof(IP_INTERFACE_INFO) );
		ULONG ulOutBufLen = sizeof(IP_INTERFACE_INFO);
		DWORD dwRetVal = 0;


		// Make an initial call to GetInterfaceInfo to get
		// the necessary size in the ulOutBufLen variable
		if ( GetInterfaceInfo(pInfo, &ulOutBufLen) == ERROR_INSUFFICIENT_BUFFER) {
			free(pInfo);
			pInfo = (IP_INTERFACE_INFO *) malloc (ulOutBufLen);
		}

		// Make a second call to GetInterfaceInfo to get
		// the actual data we need
		if ((dwRetVal = GetInterfaceInfo(pInfo, &ulOutBufLen)) == NO_ERROR ) {

			printf("\tNum Adapters: %ld\n", pInfo->NumAdapters);//网卡数量
			for (int i=0;i<pInfo->NumAdapters;i++)
			{
				SetAdapterIndex(pInfo->Adapter[i].Index);

				char msg[321];
				sprintf(msg, "Adapter Name: %ws\nAdapter Index: %ld\n",pInfo->Adapter[i].Name, pInfo->Adapter[i].Index );
				//MessageBox(0,msg,"",0);
				printf("\tAdapter Name: %ws\n", pInfo->Adapter[i].Name);
				printf("\tAdapter Index: %ld\n", pInfo->Adapter[i].Index);

			}
			 
			return true;
		}
		else {
			printf("GetInterfaceInfo failed.\n");
			LPVOID lpMsgBuf;

			if (FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwRetVal,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL ))  {
					printf("\tError: %s", lpMsgBuf);
				}
				LocalFree( lpMsgBuf );

				free(pInfo);
				pInfo=NULL;
				return false;
		}

	}

	// 获取网络状态
	bool getNetworkStatus(  DWORD & inBytes,   DWORD & outBytes )
	{
		// 网卡信息
		MIB_IFROW MibIfRow;
		MibIfRow.dwIndex=currAdapterIndex;

		if ( GetIfEntry(&MibIfRow) == NO_ERROR ) 
		{
			inBytes = MibIfRow.dwInOctets;
			outBytes = MibIfRow.dwOutOctets;
			return true;
		}
		return false;
	}


};
