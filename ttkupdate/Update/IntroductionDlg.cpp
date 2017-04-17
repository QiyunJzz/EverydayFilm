// IntroductionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "IntroductionDlg.h"
#include "EventID.h"


// CIntroductionDlg �Ի���

IMPLEMENT_DYNAMIC(CIntroductionDlg, CDialog)

CIntroductionDlg::CIntroductionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIntroductionDlg::IDD, pParent)
{

}

CIntroductionDlg::~CIntroductionDlg()
{
}

void CIntroductionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIntroductionDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CIntroductionDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BTN_NEXT, &CIntroductionDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(ID_BTN_CANCEL, &CIntroductionDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CIntroductionDlg ��Ϣ�������

void CIntroductionDlg::OnBnClickedCancel()
{
	//GetParent()->SendMessage(WM_CLOSE);
}

void CIntroductionDlg::OnBnClickedBtnNext()
{
	GetParent()->SendMessage(WM_INTRODUCTION_NEXT);
}

void CIntroductionDlg::OnBnClickedBtnCancel()
{
	GetParent()->SendMessage(WM_UPDATE_CANCEL);
}
