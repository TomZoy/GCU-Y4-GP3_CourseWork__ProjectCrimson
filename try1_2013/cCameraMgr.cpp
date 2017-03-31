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
	

	if (firstCall)
	{
		currentCamera = getCamera(gameGameras.begin()->first);
		firstCall = false;
	};

	if (m_InputMgr->isKeyDown(VK_TAB))
	{

		
		cCamera *newCamera = getCamera("camera1");
		if (newCamera != currentCamera)
		{
			currentCamera = getCamera("camera1");
		}
		else
		{
			//getCamera("camera2")->setTheCameraPos(glm::vec3(0.0f, 0.0f, 15.0f));
			currentCamera = getCamera("camera2");

		}
		
	};

	currentCamera->update();

}

void cCameraMgr::updateCamera(glm::vec3 position)
{
	getCamera("camera2")->setTheCameraPos(glm::vec3(position.x + 1.0f, position.y + 1.0f, -position.z));
	getCamera("camera2")->setTheCameraLookAt(glm::vec3(position.x, position.y-1.0f, -(position.z+15.0f)));

}

cCamera* cCameraMgr::getCamera(LPCSTR sndName){
	map<LPCSTR, cCamera*>::iterator snd = gameGameras.find(sndName);
	if (snd != gameGameras.end())
	{
		return snd->second;
	}
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
