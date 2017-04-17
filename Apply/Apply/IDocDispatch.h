#pragma once
#include "oaidl.h"
#include "ExDispid.h"

#ifndef _IMPIDISPATCH_H_
#define _IMPIDISPATCH_H_

class IDocDispatch :
	public IDispatch
{
protected:
	ULONG			m_cRef;

public:
	IDocDispatch(void);
	~IDocDispatch(void);
	
	STDMETHODIMP QueryInterface(REFIID, void**);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	
	//IDispatch
	STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
	STDMETHODIMP GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ ITypeInfo** ppTInfo);
	STDMETHODIMP GetIDsOfNames(			//ȡһ�����������Ʋ����������ID�����DISPID
		/* [in] */ REFIID riid,
		/* [size_is][in] */ LPOLESTR* rgszNames,
		/* [in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ DISPID* rgDispId);
	STDMETHODIMP Invoke(				//���Խ�DISPID��Ϊ��������ָ�������
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr);
};
#endif