/*
==========================================================================
cCameradMgr.h
==========================================================================
*/

#ifndef _CAMERAMGR_H
#define _CAMERAMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "cInputMgr.h"

using namespace std;

class cCameraMgr
{
private:
	static cCameraMgr* pInstance;
	cInputMgr* m_InputMgr;

protected:
	cCameraMgr();
	~cCameraMgr();

	bool firstCall = true;
	cCamera *currentCamera;
	map <LPCSTR, cCamera*> gameGameras;



public:
	void updateCamera();
	cCamera* cCameraMgr::getCamera(LPCSTR sndName);
	static cCameraMgr* getInstance();
	void attachInputMgr(cInputMgr* inputMgr);
	cCamera *getCurrentCamera();
	void add(LPCSTR,cCamera*);
	void updateCamera(glm::vec3 position);


};
#endif