/*
==================================================================================
cSceneMgr.cpp
==================================================================================
*/

#include "cSceneMgr.h"
#include "GameConstants.h"

cSceneMgr* cSceneMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSceneMgr::cSceneMgr()
{

}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSceneMgr* cSceneMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSceneMgr();
	}

	return cSceneMgr::pInstance;
}




void cSceneMgr::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}



void cSceneMgr::takeInput()
{



	switch (gameScreen)
	{
	case intro:
		if (m_InputMgr->isKeyDown(VK_SPACE))
		{
			gameScreen = guide;
		}


		break;
	case guide:
		if (m_InputMgr->isKeyDown(VK_SPACE))
		{
			gameScreen = game;
		}

		break;
	case game:



		break;
	case gameOver:

		break;
	default:
		break;
	}






}



cSceneMgr::~cSceneMgr()
{

}
