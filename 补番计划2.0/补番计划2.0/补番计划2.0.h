
// �����ƻ�2.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C�����ƻ�20App:
// �йش����ʵ�֣������ �����ƻ�2.0.cpp
//

class C�����ƻ�20App : public CWinApp
{
public:
	C�����ƻ�20App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C�����ƻ�20App theApp;