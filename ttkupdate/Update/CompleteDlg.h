#pragma once
#include "SuperLink.h"

// CCompleteDlg �Ի���

class CCompleteDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompleteDlg)

public:
	CCompleteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCompleteDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMPLETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	CSuperLink m_linkSite;
    CFont    m_Font;    

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
