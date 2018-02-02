#pragma once

#include <iphlpapi.h>
#pragma comment(lib,"IPHlpApi.Lib")


/************************************************************************/
/* 

��ñ���������Ϣ,�Լ���Ӧ��������������

*/
/************************************************************************/
class CNetStat
{
	 

	int currAdapterIndex;//ָ����ǰ����,���ڻ�ȡ

public:
	PIP_INTERFACE_INFO pInfo;//������Ϣ

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
	
	//����Ҫ���ӵ�����������
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

			printf("\tNum Adapters: %ld\n", pInfo->NumAdapters);//��������
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

	// ��ȡ����״̬
	bool getNetworkStatus(  DWORD & inBytes,   DWORD & outBytes )
	{
		// ������Ϣ
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
