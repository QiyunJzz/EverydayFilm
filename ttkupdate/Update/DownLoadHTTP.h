#ifndef __DOWNLOADHTTP__H__
#define __DOWNLOADHTTP__H__
#pragma once
#include "downloadpublic.h"

class CDownLoadHTTP :	//HTTP Э��������
	public CDownLoadPublic
{
public:
	CDownLoadHTTP(void);
	~CDownLoadHTTP(void);


public:
	BOOL RequestHttpData(BOOL bGet, char *szTailData=NULL, int *pnTailSize=NULL);	//����HTTP����
	CTime ConvertHttpTimeString(CString strTimeGMT );								//ת��http ʱ��Ϊ�ַ�
	CString FindAfterFlagString(LPCTSTR lpszFoundStr, CString strOrg);				//���� ������ַ�
	BOOL ParseResponseString(CString strResponseString, OUT BOOL &bRetryRequest);	//������Ӧ�ַ�
	DWORD GetResponseCode(CString strLineText );									//�õ���Ӧ����
	BOOL SendRequest(LPCTSTR lpszReq, OUT CString &strResponse, char *szTailData=NULL, int *pnTailSize=NULL);		//��������
	CString GetRequestStr(BOOL bGet);					//�õ������ַ�

	virtual BOOL DownloadOnce();				//�Ƿ���������
	virtual BOOL GetRemoteSiteInfoPro();			//�õ�Զ��վ����Ϣ



};

#endif