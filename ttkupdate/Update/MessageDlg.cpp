// MessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "MessageDlg.h"


// CMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CMessageDlg, CDialog)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageDlg::IDD, pParent)
{

}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_CANCEL, &CMessageDlg::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDOK, &CMessageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CMessageDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMessageDlg ��Ϣ�������

BOOL CMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(NULL, TRUE);			// ���ô�ͼ��
	SetIcon(NULL, FALSE);		// ����Сͼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMessageDlg::OnBnClickedBtnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CMessageDlg::OnBnClickedOk()
{
	OnOK();
}

void CMessageDlg::OnBnClickedOk2()
{
	OnOK();
}
