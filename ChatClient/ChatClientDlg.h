
// ChatClientDlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "CConnectSocket.h"
#include "CClientID.h"
#include "CLogInDlg.h"


// CChatClientDlg 대화 상자
class CChatClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CConnectSocket	m_Socket;
	CClientID m_CID;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_List;
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnEnChangeEditSend();
	afx_msg void OnBnClickedButtonSend();
	CString m_strMessage;
	CListBox m_List_ID;
	BOOL btn;
	CEdit m_edit_connect;
	CIPAddressCtrl sadfsdf;
	CButton m_ButtonReset;
	CEdit m_EditMyID;
	CButton m_ButtonLogIn;
	CEdit m_EditSend;
	CButton m_ButtonSend;
	CListBox m_ListUser;
	afx_msg void OnDblclkListUser();

private:
	CString ClientName;
public:
	afx_msg void OnBnClickedButtonReset();
};
