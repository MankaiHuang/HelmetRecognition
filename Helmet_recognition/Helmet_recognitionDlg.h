
// Helmet_recognitionDlg.h : ͷ�ļ�
//

#pragma once

#include "MatWnd.h"
#include "SVMTraining.h"
#include "afxcmn.h"
#include "Detector.h"

// CHelmet_recognitionDlg �Ի���
class CHelmet_recognitionDlg : public CDialogEx
{
// ����
public:
	CHelmet_recognitionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HELMET_RECOGNITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnOpenFile();
	afx_msg void OnCloseFile();
	afx_msg void OnOpenCamera();
	afx_msg void OnCloseCamera();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedStaticMat();
	DECLARE_MESSAGE_MAP()

	void AddInfo(CString &szInfo);

private:
	// ��Ƶ����
	VideoCapture m_vcVideo;
	// Mat��ʾ����
	CMatWnd m_wndMat;
	// ��Ƶ�ļ��Ƿ�ѭ������
	bool m_bLoop;
	// ��Ƶ�ļ�ʣ��Ƶ��
	int m_nFrameCount;

	// ����������
	SVMTraining svm_detector_obj;
	// �����
	Detector detector;
	// �б����
	CListCtrl m_lstInfo;
};
