﻿
// ChatClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"
#include "CClientID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CString GetMyIP()
{
	CString ipAddr;
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		char name[256];
		if (gethostname(name, sizeof(name)) == 0)
		{
			PHOSTENT hostinfo = gethostbyname(name);
			if (hostinfo != NULL)
			{
				ipAddr = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	return ipAddr;
}



// CChatClientDlg 대화 상자



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_ButtonReset);
	DDX_Control(pDX, IDC_EDIT_MYID, m_EditMyID);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_ButtonLogIn);
	DDX_Control(pDX, IDC_EDIT_Send, m_EditSend);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_ButtonSend);
	DDX_Control(pDX, IDC_LIST_USER, m_ListUser);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST, &CChatClientDlg::OnLbnSelchangeList)
	ON_EN_CHANGE(IDC_EDIT_Send, &CChatClientDlg::OnEnChangeEditSend)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatClientDlg::OnBnClickedButtonSend)
	ON_LBN_DBLCLK(IDC_LIST_USER, &CChatClientDlg::OnDblclkListUser)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CChatClientDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CChatClientDlg 메시지 처리기

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CString strID;
	strID = m_CID.setCID();
	SetDlgItemText(IDC_EDIT_MYID, strID);
	if (strID == L"")
	{
		exit(0);
	}
	btn = FALSE;
	m_EditMyID.EnableWindow(FALSE);
	m_ButtonLogIn.EnableWindow(FALSE);

	if (m_Socket.Create() && m_Socket.Connect(_T("172.1.2.189"), 21000))
	{
		CString strIP = GetMyIP();
		strID = L":" + strID + L"[" + strIP + L"]" + L"::";
		UpdateData(TRUE);
		m_Socket.Send(strID, strID.GetLength() * 2);
		UpdateData(FALSE);
		m_CID.getCID(L"");
		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("ERROR : FAILED TO CONNECT SERVER"));
		PostQuitMessage(0);
		return FALSE;
	}
	  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnLbnSelchangeList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChatClientDlg::OnEnChangeEditSend()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChatClientDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMsg, strTmp, strIP, strID, strCID;

	GetDlgItemText(IDC_EDIT_MYID, strID);
	GetDlgItemText(IDC_EDIT_Send, strMsg);
	strIP = GetMyIP();
	strCID = m_CID.setCID();
	strTmp = strIP + L":" + strID + L":" + strMsg + L":" + strCID;

	if (strMsg != L"")
	{
		UpdateData(TRUE);
		m_Socket.Send((LPVOID)(LPCTSTR)strTmp, strTmp.GetLength() * 2);
		SetDlgItemText(IDC_EDIT_Send, L"");
		UpdateData(FALSE);
	}

}


void CChatClientDlg::OnDblclkListUser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_ListUser.GetCurSel();
	CString strTmp, Tmp;

	m_ListUser.GetText(index, strTmp);
	AfxExtractSubString(Tmp, strTmp, 0, '[');
	m_CID.getCID(Tmp);
}

void CChatClientDlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTmp = L"";
	m_CID.getCID(strTmp);
}
