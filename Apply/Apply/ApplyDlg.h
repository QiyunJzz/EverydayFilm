// ApplyDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"


class CApplyDlg : public CDialog
{
public:
	CApplyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_APPLY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;


public:
	void NewShowWnd();
	void SetTrans(int itrans);

private:


public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
