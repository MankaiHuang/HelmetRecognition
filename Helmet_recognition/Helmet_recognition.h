
// Helmet_recognition.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "Resource.h"		// ������


// CHelmet_recognitionApp:
// �йش����ʵ�֣������ Helmet_recognition.cpp
//

class CHelmet_recognitionApp : public CWinApp
{
public:
	CHelmet_recognitionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CHelmet_recognitionApp theApp;