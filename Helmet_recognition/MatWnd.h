#pragma once

#include "CvvImage.h"

// CMatWnd

class CMatWnd : public CWnd
{
	DECLARE_DYNAMIC(CMatWnd)

public:
	CMatWnd();
	virtual ~CMatWnd();

public:
	void UpdateMat();
	void ReleaseMat();

public:
	Mat m_mat;

protected:
	void DrawMatToHDC(Mat &mat);
	void DrawPicToHDC(IplImage *img);

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	// ��¼��Ƶͼ������
	CRect m_rtImage;
	// ��¼��ǰ���ڵ�����
	CRect m_rtWnd;
};
