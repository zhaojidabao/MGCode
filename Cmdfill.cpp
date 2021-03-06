// CmdFill.cpp: implementation of the CCmdFill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "hl.h"
#include "CmdFill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCmdFill::CCmdFill(CHLDoc* pDoc,FILLDATA fillnew,FILLDATA fillold)
{
	commandName.LoadString(IDS_COMMAND_FILL);
	m_pDoc=pDoc;
//	m_chainOld=pDoc->GetChain();
	m_chainOld.StoreChain(pDoc->GetChain());
	m_pDoc->FillCmd(fillnew);
//	m_chainNew=pDoc->GetChain();
	m_chainNew.StoreChain(pDoc->GetChain());
	m_bFirst=TRUE;
}

CCmdFill::~CCmdFill()
{
}

BOOL CCmdFill::Do(BOOL bRedo)
{
	if(m_bFirst)
		m_bFirst=FALSE;
	else
		m_pDoc->SetChain(m_chainNew);
	return TRUE;
}

BOOL CCmdFill::Undo(BOOL bRedo)
{
	m_pDoc->SetChain(m_chainOld);
	return TRUE;
}
