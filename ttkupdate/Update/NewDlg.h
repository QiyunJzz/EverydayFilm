#pragma once
#include "SuperLink.h"

// CNewDlg �Ի���

class CNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW };

private:
//	CSuperLink m_linkSite;
	CBitmap m_bmpBk;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnOk();
};
