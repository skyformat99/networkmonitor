// NetWorkAdapterSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "networkmonitor.h"
#include "NetWorkAdapterSetDlg.h"
#include ".\networkadaptersetdlg.h"


// CNetWorkAdapterSetDlg 对话框

IMPLEMENT_DYNAMIC(CNetWorkAdapterSetDlg, CDialog)
CNetWorkAdapterSetDlg::CNetWorkAdapterSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetWorkAdapterSetDlg::IDD, pParent)
{
}

CNetWorkAdapterSetDlg::~CNetWorkAdapterSetDlg()
{
}

void CNetWorkAdapterSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
}


BEGIN_MESSAGE_MAP(CNetWorkAdapterSetDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
 
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


#include "NetStat.h"

// CNetWorkAdapterSetDlg 消息处理程序	
extern CNetStat cnet;
extern void FileSize_Format(DWORD dwBytes,char* msg);

BOOL CNetWorkAdapterSetDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	m_listctrl.InsertColumn(0,"索引",LVCFMT_LEFT,50,-1);
	m_listctrl.InsertColumn(1,"名称",LVCFMT_LEFT,170,-1);
	m_listctrl.InsertColumn(2,"流量",LVCFMT_LEFT,190,-1);
	m_listctrl.SetExtendedStyle(m_listctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//详细报表
	m_listctrl.ModifyStyle(NULL,LVS_REPORT);
	
	//枚举网卡
	cnet.EnumAdapter();

	for (int i=0;i<cnet.pInfo->NumAdapters;i++)
	{
		//SetAdapterIndex(cnet.pInfo->Adapter[i].Index);

		char msg[321];
		sprintf(msg, "Adapter Name: %ws\nAdapter Index: %ld\n",cnet.pInfo->Adapter[i].Name, cnet.pInfo->Adapter[i].Index );

		m_listctrl.SetItemData(m_listctrl.GetItemCount(),cnet.pInfo->Adapter[i].Index );

		//索引
		char idx[321];
		sprintf(idx,"%d",cnet.pInfo->Adapter[i].Index );
		m_listctrl.InsertItem(m_listctrl.GetItemCount(), idx );
		
		 

		//名称
		sprintf(msg, "%ws",cnet.pInfo->Adapter[i].Name);
		m_listctrl.SetItemText(m_listctrl.GetItemCount()-1,1,msg );

		//流量
		// 网卡信息
		MIB_IFROW MibIfRow;
		MibIfRow.dwIndex= cnet.pInfo->Adapter[i].Index;
		GetIfEntry(&MibIfRow);
		 
		DWORD	inBytes = MibIfRow.dwInOctets;
		DWORD	outBytes = MibIfRow.dwOutOctets;
		
		char inmsg[321];
		FileSize_Format(inBytes,inmsg);
		char outmsg[321];
		FileSize_Format(outBytes,outmsg);

		sprintf(msg,"下载[%s] 上传[%s]" , inmsg  , outmsg );
	 
		m_listctrl.SetItemText(m_listctrl.GetItemCount()-1,2,msg);
	}

	//默认选第一个
	m_listctrl.SetSelectionMark(0);

	return TRUE;
}

int CNetWorkAdapterSetDlg::GetSelectedItem()
{
	POSITION posti = m_listctrl.GetFirstSelectedItemPosition();
	if(posti == NULL)
		return -1;
	DWORD dwSel = m_listctrl.GetNextSelectedItem(posti);
	return dwSel;
}

extern BOOL g_bFirstCheck;
void CNetWorkAdapterSetDlg::OnBnClickedOk()
{

	int currentSelect=  GetSelectedItem();
	if(currentSelect>=0)//选择某项
	{	
		DWORD idx =atoi(m_listctrl.GetItemText(currentSelect,0));
		char m[33];
		sprintf(m,"%d %d",currentSelect,idx);
		//AfxMessageBox(m);

		cnet.SetAdapterIndex(idx);
		g_bFirstCheck=TRUE;

		// TODO: 在此添加控件通知处理程序代码
		OnOK();

	}
}

void CNetWorkAdapterSetDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedOk();

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
