/*
==========================================================================
cSceneMgr.h
==========================================================================
*/

#ifndef _SCENEMGR_H
#define _SCENEMGR_H

//Headers
#include "GameConstants.h"
#include "cInputMgr.h"

using namespace std;

class cSceneMgr
{
private:
	static cSceneMgr* pInstance;
	cInputMgr* m_InputMgr;


protected:
	cSceneMgr();
	~cSceneMgr();


public:
	static cSceneMgr* getInstance();
	void attachInputMgr(cInputMgr* inputMgr);
	void takeInput();


};
#endif