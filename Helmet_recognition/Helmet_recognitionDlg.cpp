
// Helmet_recognitionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helmet_recognition.h"
#include "Helmet_recognitionDlg.h"
#include "Utils.h"
#include "SVMTraining.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ��Ƶ��ʾƵ��(��λ������)
#define WM_TIMER_PLAYER   WM_USER+1000
#define FRAME_INFINITE   -99999


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHelmet_recognitionDlg �Ի���




CHelmet_recognitionDlg::CHelmet_recognitionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelmet_recognitionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	detector.Load();
}

void CHelmet_recognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MAT, m_wndMat);
	DDX_Control(pDX, IDC_LIST_INFO, m_lstInfo);
}

BEGIN_MESSAGE_MAP(CHelmet_recognitionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_WM_TIMER()
	ON_COMMAND(IDM_OPEN_FILE, &CHelmet_recognitionDlg::OnOpenFile)
	ON_COMMAND(IDM_CLOSE_FILE, &CHelmet_recognitionDlg::OnCloseFile)

	ON_COMMAND(IDM_OPEN_CAMERA, &CHelmet_recognitionDlg::OnOpenCamera)
	ON_COMMAND(IDM_CLOSE_CAMERA, &CHelmet_recognitionDlg::OnCloseCamera)

	ON_BN_CLICKED(IDC_BUTTONOPEN, &CHelmet_recognitionDlg::OnOpenFile)
END_MESSAGE_MAP()


// CHelmet_recognitionDlg ��Ϣ�������

BOOL CHelmet_recognitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼ���б�
	LONG lStyle = ::GetWindowLong(m_lstInfo.m_hWnd, GWL_STYLE); //��ȡ��ǰ����style
	lStyle |= LVS_REPORT;   //��¼��ʽ
	lStyle |= LVS_SINGLESEL; //����ѡ��Ĭ��ʱ���Զ���ѡ��
	lStyle |= LVS_SHOWSELALWAYS;
	::SetWindowLong(m_lstInfo.m_hWnd, GWL_STYLE, lStyle);//����style

	//����listCtrl����չ��ʽ
	DWORD dwStyle = m_lstInfo.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и���
	m_lstInfo.SetExtendedStyle(dwStyle); 

	m_lstInfo.InsertColumn(0, _T("ʱ��"), LVCFMT_LEFT, 130);
	m_lstInfo.InsertColumn(1, _T("��Ϣ"), LVCFMT_LEFT, 150);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHelmet_recognitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHelmet_recognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHelmet_recognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ����Ƶ�ļ�
void CHelmet_recognitionDlg::OnOpenFile()
{
	// ���ļ��Ի���ı�����
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		NULL, NULL);
	dlg.m_ofn.lpstrTitle = _T("����Ƶ�ļ�");

	// �ж��Ƿ���ͼƬ
	if( dlg.DoModal() != IDOK )                    
		return;

	// ��ȡͼƬ·��
	CString path = dlg.GetPathName();
	if (path.GetLength() > 0)
	{
		OnCloseFile();
		// ����Ƶ�ļ�
		if(!m_vcVideo.open(CUtils::Str2Stda(path)))
		{
			MessageBox(_T("��Ƶ�ļ���ʧ��"));
		}
		else
		{
			// ��ȡ��ƵƵ��,����ÿ֮֡��ļ��������
			int nFps = (int)m_vcVideo.get(CV_CAP_PROP_FPS);
			int nElapse = (int)(1000.0 / nFps);
			// ��ȡ��ƵƵ��
			m_nFrameCount = (int)m_vcVideo.get(CV_CAP_PROP_FRAME_COUNT);
			
			this->AddInfo(dlg.GetFileName());

			// ������ʱ������֡����
			SetTimer(WM_TIMER_PLAYER, nElapse, NULL);		
		}
	}
}

// �ر���Ƶ�ļ�
void CHelmet_recognitionDlg::OnCloseFile()
{
	KillTimer(WM_TIMER_PLAYER);
	if (m_vcVideo.isOpened())
	{
		m_vcVideo.release();
		m_wndMat.ReleaseMat();
	}	
}

// ������ͷ
void CHelmet_recognitionDlg::OnOpenCamera()
{
	// ���������Ĭ�ϵ�ǰ�豸Ϊ0
	if(!m_vcVideo.open(0))
	{
		MessageBox(_T("������ͷʧ��"));
	}
	else
	{
		// ��ʾ����֡��
		m_nFrameCount = FRAME_INFINITE;
		// ������ʱ��
		SetTimer(WM_TIMER_PLAYER, 40, NULL);
	}
}

// �ر�����ͷ
void CHelmet_recognitionDlg::OnCloseCamera()
{
	KillTimer(WM_TIMER_PLAYER);
	if (m_vcVideo.isOpened())
	{
		m_vcVideo.release();
		m_wndMat.ReleaseMat();
	}
}

// ��ʱ����Ӧ����
void CHelmet_recognitionDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == WM_TIMER_PLAYER)
	{
		// ����������Ƶ֡������֡������0
		if (m_nFrameCount == FRAME_INFINITE || --m_nFrameCount > 0)
		{
			m_vcVideo >> m_wndMat.m_mat;
		
			if (!m_wndMat.m_mat.empty())
			{
				detector.HOGScan(m_wndMat.m_mat);
				m_wndMat.UpdateMat();
			}			
		}
		else
		{
			// ѭ�����ţ����Ƶ���Ƶ��һ֡
			if (m_bLoop == true)
			{
				m_vcVideo.set(CV_CAP_PROP_POS_AVI_RATIO, 0.0);
				m_nFrameCount = (int)m_vcVideo.get(CV_CAP_PROP_FRAME_COUNT);
			}
			else // ��ѭ�����ţ��������Ƶ�����رն�ʱ��
			{
				KillTimer(WM_TIMER_PLAYER);
				OnCloseFile();
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CHelmet_recognitionDlg::OnStnClickedStaticMat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CHelmet_recognitionDlg::AddInfo( CString &szInfo )
{
	CTime t = CTime::GetCurrentTime();	
	m_lstInfo.InsertItem(0, t.Format(_T("%Y-%m-%d %H:%M:%S")));
	m_lstInfo.SetItemText(0, 1, szInfo);
}
