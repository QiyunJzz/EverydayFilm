#ifndef __DOWNLOADMTR__H__
#define __DOWNLOADMTR__H__  
#pragma once // MTR - MultiThread Resume : ���̶߳ϵ�����
#include "DownloadFtp.h"
#include "DownloadHttp.h"
#include <Afxmt.h>


#define NOTE_DownloadMTR  _T("FTP HTTP ��ʼ����")

#define DEFAULT_THREAD_COUNT		1			// Ĭ������һ���ļ����õ��߳���
#define MAX_DOWNLOAD_THREAD_COUNT	16			// ����һ���ļ����ʹ�õ��߳���

// ���������������Ϣ
typedef struct tagDownLoadCellInfo
{
	int nWillDownloadStartPos;			// Ҫ�����ļ��Ŀ�ʼλ��
	int nWillDownloadSize;				// ������Ҫ���صĴ�С��-1��ʾһֱ���ص��ļ�β
	DWORD nDownloadedSize;				// ���߳������صĴ�С
}DownLoadCellInfo;

// ������Ϣ
typedef struct tagBaseDownInfo
{
	DWORD dwThreadCount;				// ���ļ��ɶ��ٸ��߳�������
}BaseDownInfo;


class CDownLoadMTR
{
public:
	CDownLoadMTR(void);
	~CDownLoadMTR(void);

	int GetTotalDownloadedSize_ThisTimes();			//��ǰʱ�� �õ������ܴ�С
	int GetTotalDownloadedSize();				//�õ������ܴ�С
	int GetFileTotaleSize();					//�õ��ļ��ܴ�С
	static CString GetLocalFileNameByURL(LPCTSTR lpszDownloadURL);		//ͨ��url�õ������ļ���
	void StopDownload();						//ֹͣ����
	DWORD GetDownloadElapsedTime();				//���ع�ȥʱ��
	BOOL StartDownload();					    // ģ��ϵ�����
	BOOL Download (								//����
		LPCTSTR lpszDownloadURL,
		LPCTSTR lpszSavePath,
		LPCTSTR lpszSaveOnlyFileName,
		LPCTSTR lpszUsername=NULL,
		LPCTSTR lpszPassword=NULL,
		BOOL bForceDownload=FALSE
		);
	BOOL SetThreadCount (int nThreadCount);					//�����̸߳���

	void CallbackSaveDownloadInfo(int nIndex, int nDownloadedSize, int nSimpleSaveSize);  //���ñ���������Ϣ
	BOOL ThreadProcDownloadMTR();				//�߳�����

public:

	void StandardSaveFileName();					//��׼�����ļ���
	int GetDownloadInfoWholeSize();					//�õ�������Ϣ��С
	int FindIndexByThreadHandle(HANDLE hThread);     //ͨ���߳��ҵ����
	ENUM_DOWNLOAD_RESULT WaitForDownloadFinished();		//�ȴ��������
	BOOL GetDownloadResult();				//�õ����ؽ��
	BOOL AttemperDownloadTask(int nIndex);  //������������
	int GetUndownloadMaxBytes(int &nUndownloadBytes);			//�Ƕϵ���������ֽ�
	BOOL HandleDownloadFinished (ENUM_DOWNLOAD_RESULT eDownloadResult);		//�����������
	BOOL SaveDownloadInfo();				//����������Ϣ
	BOOL AssignDownloadTask();				//������������
	BOOL DownloadInfoIsValid();				//������Ϣ����Ч��
	BOOL ReadDownloadInfo();				//��ȡ������Ϣ
	CString GetTempFilePath();				//�õ��ļ�·��
	int StartMTRDownload();					//��ʼ MTR ����
	void DeleteDownloadObjectAndDataMTR();		//ɾ�����ض����MTR����
	void DeleteDownloadObjectInfo();				//ɾ�����ض�����Ϣ
	BOOL CreateDownloadObjectAndDataMTR();				//�������ض����MTR����
	CDownLoadPublic* CreateDownloadObject(int nCount=1);		//�������ض���
	void DeleteDownloadObject(CDownLoadPublic *pDownloadPub);		//ɾ�����ض���

public:

	CString m_strSavePath, m_strSaveOnlyFileName, m_strSavePathFileName, m_strDownloadURL;	//����·�� �����ļ��� ����·���� ����URL
	CString m_strProtocolType;				//Э������
	int m_nThreadCount;							// �߳���
	CDownLoadPublic *m_pDownloadPub_Info;			// ȡվ����Ϣ����
	CDownLoadPublic	*m_pDownloadPub_MTR;			// ���߳����ض���
	BaseDownInfo	m_BaseDownInfo;				// ���ػ�����Ϣ���߳�����
	DownLoadCellInfo *m_pDownloadCellInfo;	// �������ض���Ĳ���
	HANDLE m_hEvtEndModule;			// ģ������¼�

	int m_nTotalDownloadedSize_ThisTimes;		// ��ʾ��������������������ܹ����ص��ֽ���
	CCriticalSection m_csDownloadedData;			//�ٽ���

	BOOL m_bForceDownload;							//�Ƿ��������أ�
	HANDLE m_hThread;								//�߳̾��
	DWORD m_dwDownloadStartTime;					//���ؿ�ʼʱ��

	BOOL m_bFileExist,m_bDownStart,m_bDownError;
};

#endif