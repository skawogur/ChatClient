// CLogInDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ChatClient.h"
#include "CLogInDlg.h"
#include "afxdialogex.h"



// CLogInDlg 대화 상자

IMPLEMENT_DYNAMIC(CLogInDlg, CDialogEx);

CLogInDlg::CLogInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{

}

CLogInDlg::~CLogInDlg()
{
}

void CLogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogInDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_MYNAME, &CLogInDlg::OnEnChangeEditMyname)
	ON_BN_CLICKED(IDC_BUTTON_MYNAME, &CLogInDlg::OnBnClickedButtonMyname)
END_MESSAGE_MAP()


// CLogInDlg 메시지 처리기


void CLogInDlg::OnEnChangeEditMyname()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLogInDlg::OnBnClickedButtonMyname()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT_MYNAME, MyName);
	if (MyName == L"")
	{
		AfxMessageBox(L"다시 입력해라");
	}
	else
	{

		m_ClientID.getCID(MyName);
		AfxMessageBox(L"채팅방 이동");
		EndDialog(0);
	}

}