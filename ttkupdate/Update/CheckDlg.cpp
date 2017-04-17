// CheckDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "CheckDlg.h"
#include "EventID.h"




// ����������̺߳���
UINT __cdecl ThreadProcConnectionServer(LPVOID lpParameter)
{
	CCheckDlg *pCheck = (CCheckDlg*)lpParameter;
	ASSERT(pCheck);
	pCheck->ShowProcessCtrl();
	TRACE(_T("ִ�����\n"));
	return TRUE;
}

// CCheckDlg �Ի���

IMPLEMENT_DYNAMIC(CCheckDlg, CDialog)

CCheckDlg::CCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckDlg::IDD, pParent)
{

}

CCheckDlg::~CCheckDlg()
{
}

void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_CANCEL, &CCheckDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CCheckDlg ��Ϣ�������

void CCheckDlg::OnBnClickedBtnCancel()
{
	GetParent()->SendMessage(WM_UPDATE_CANCEL,(WPARAM)pCheckThread);
}

BOOL CCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CProgressCtrl *pProcess = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS_CONNECTION_SERVER);
	pProcess->SetRange(0,100);

	return TRUE; 
}


void CCheckDlg::ShowWindowEx(BOOL m_bShow)
{
	ShowWindow(m_bShow);
	if(!m_bShow) 	return;

	pCheckThread=NULL;
	pCheckThread=AfxBeginThread(ThreadProcConnectionServer,this);
}

void CCheckDlg::ShowProcessCtrl()
{
	CProgressCtrl *pProcess = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS_CONNECTION_SERVER);
	for(int i=1;i<=100;i++)
	{
		pProcess->SetPos(i);
		Sleep(20);
	}
	GetParent()->SendMessage(WM_CHECK_NEXT_DOWNLOAD);
}