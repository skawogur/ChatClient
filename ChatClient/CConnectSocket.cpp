#include "pch.h"
#include "CConnectSocket.h"
#include "ChatClientDlg.h"

CString GetMyIP1()
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

void CConnectSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnected from server!"));
	::PostQuitMessage(0);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	USES_CONVERSION;
	CString strMsg, strIP, strID, strCID, strTmp, strMyName;
	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CChatClientDlg* pMain = (CChatClientDlg*)AfxGetMainWnd();
		strTmp.Format(_T("%s"), szBuffer);

		AfxExtractSubString(strIP, strTmp, 0, ':');
		AfxExtractSubString(strID, strTmp, 1, ':');
		AfxExtractSubString(strMsg, strTmp, 2, ':');
		AfxExtractSubString(strCID, strTmp, 3, ':');
		AfxExtractSubString(strMyName, strTmp, 4, ':');
		if (strMsg != L"")
		{
			strTmp = L"[" + strIP + L"]" + strID + L":" + strMsg;
			pMain->m_List.AddString(strTmp);
			pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
		}
		else if(strID != L"")
		{

			pMain->m_ListUser.AddString(strID);
			strTmp = strID + L"님이 입장하셨습니다.";
			pMain->m_List.AddString(strTmp);
			pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
		}
		else if (strMyName != L"")
		{
			pMain->m_ListUser.AddString(strMyName);
			//pMain->m_ListUser.AddString(strID);
			//strTmp = strID + L"님이 입장하셨습니다.";
			//pMain->m_List.AddString(strTmp);
			//pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
		}
		CSocket::OnReceive(nErrorCode);
	}
}