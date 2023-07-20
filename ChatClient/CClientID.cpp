#include "pch.h"
#include "CClientID.h"



void CClientID::getCID(CString strTmp)
{
	CID = strTmp;
}

CString CClientID::setCID()
{
	return CID;
}