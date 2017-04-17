// ExitMessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "ExitMessageDlg.h"
#include "EventID.h"


// CExitMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CExitMessageDlg, CDialog)

CExitMessageDlg::CExitMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExitMessageDlg::IDD, pParent)
{

}

CExitMessageDlg::~CExitMessageDlg()
{
}

void CExitMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExitMessageDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_OK, &CExitMessageDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(ID_BTN_CANCEL, &CExitMessageDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CExitMessageDlg ��Ϣ�������

void CExitMessageDlg::OnBnClickedBtnOk()
{
	OnOK();
}

void CExitMessageDlg::OnBnClickedBtnCancel()
{
	OnCancel();
}
