// LogInDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ChatClient.h"
#include "LogInDlg.h"
#include "afxdialogex.h"


// LogInDlg 대화 상자

IMPLEMENT_DYNAMIC(LogInDlg, CDialogEx)

LogInDlg::LogInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

LogInDlg::~LogInDlg()
{
}

void LogInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LogInDlg, CDialogEx)
END_MESSAGE_MAP()


// LogInDlg 메시지 처리기
