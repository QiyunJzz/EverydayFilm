#ifndef __DOWNLOADCNTL__H__
#define __DOWNLOADCNTL__H__
#pragma once
#include "DownloadMTR.h"

// ��������
typedef struct node
{
	void *info;
	struct node *link;
}NODE;



class CDownLoadControl
{
public:
	CDownLoadControl(void);
	~CDownLoadControl(void);

	int GetTaskNum();			//�õ��������
	int AddTask( TCHAR *pszUrl, TCHAR *pszSavePath, TCHAR *pszSaveFileName, int nThreadNum,	LPCTSTR lpszUsername=NULL,
		LPCTSTR lpszPassword=NULL,BOOL bForce=FALSE); //��������
	int SelTask( int nPos );  // ѡ��һ������
	int RemoveTask();		  // ɾ��ѡ�е�����
	
	int StopTask(int nPos);		//ֹͣ����

	// ��ѯһ�������״̬
	int QueryState( int nPos, 
		int &nFileTotaleSize, 
		int &nTotalDownloadedSize,
		int &nTotalDownloadedSize_ThisTimes,
		int &nDownloadElapsedTime ); 

public:
	CDownLoadMTR *m_pCurDownloadMTR;
private:
	int m_nCurDownloadMTRPos;
	NODE *m_pHead;   // ָ��ͷ����ָ��,Ϊ��infoָ�����һ���ռ�,����������¼����Ľ�����
	CCriticalSection m_csCntl;  // ���ʹ�����
};
#endif