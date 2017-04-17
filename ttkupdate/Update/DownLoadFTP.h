#ifndef __DOWNLOADFTP__H__
#define __DOWNLOADFTP__H__
#pragma once
#include "DownLoadPublic.h"

class CDownLoadFTP :
	public CDownLoadPublic
{
public:
	CDownLoadFTP(void);
	~CDownLoadFTP(void);

public:
	BOOL Connect ();			//����
	void GetFileTimeInfo(CString strFileTime1, CString strFileTime2, CString strFileTime3);			//�õ��ļ�ʱ����Ϣ
	BOOL CreateFTPDataConnect(CSocketClient &SocketClient);					//����FTPЭ����������
	void ParseFileInfoStr(CString &strFileInfoStr);						//�����ļ���Ϣ
	virtual BOOL GetRemoteSiteInfoPro();					//�õ�Զ��վ����Ϣ����
	virtual BOOL DownloadOnce();							//�Ƿ���������
};

#endif