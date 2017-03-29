/*
==========================================================================
cSoundMgr.h
==========================================================================
*/

#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

// OpenGL Headers
#include "GameConstants.h"
#include "cSound.h"
#include "cInputMgr.h"

using namespace std;

class cSoundMgr
{
private:
	static cSoundMgr* pInstance;
	ALCcontext *m_OALContext;
	ALCdevice *m_OALDevice;
	cInputMgr* m_InputMgr;

protected:
	cSoundMgr();
	~cSoundMgr();
	map <LPCSTR, cSound*> gameSnds;
	cSound *currentSnd;
	bool firstCall = true;
	void createContext();
	void switchSound(LPCSTR sndName);


public:
	void add(LPCSTR sndName, LPCSTR fileName);
	cSound* getSnd(LPCSTR sndName);
	void deleteSnd();
	static cSoundMgr* getInstance();
	void attachInputMgr(cInputMgr* inputMgr);
	void updateSound();


};
#endif