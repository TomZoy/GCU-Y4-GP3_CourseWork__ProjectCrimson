/*
==================================================================================
cSoundMgr.cpp
==================================================================================
*/

#include "cCameraMgr.h"
#include "GameConstants.h"

cCameraMgr* cCameraMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cCameraMgr::cCameraMgr()
{
	cCamera *currentCamera = NULL;
}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cCameraMgr* cCameraMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cCameraMgr();
	}

	return cCameraMgr::pInstance;
}

void cCameraMgr::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}



void cCameraMgr::updateCamera()
{


	if (m_InputMgr->isKeyDown(VK_TAB))
	{

	};


}


void cCameraMgr::add(LPCSTR cameraName, cCamera * camera)
{
	gameGameras.insert(make_pair(cameraName, camera));
}



cCamera* cCameraMgr::getCurrentCamera()
{
	return currentCamera;
};

cCameraMgr::~cCameraMgr()
{

}
