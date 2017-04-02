/*
==================================================================================
cSoundMgr.cpp
==================================================================================
*/

#include "cSoundMgr.h"
#include "GameConstants.h"

cSoundMgr* cSoundMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSoundMgr::cSoundMgr()
{
	createContext();
}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSoundMgr* cSoundMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSoundMgr();
	}

	return cSoundMgr::pInstance;
}

void cSoundMgr::createContext()
{
	m_OALDevice = alcOpenDevice(NULL);
	if (m_OALDevice)
	{
		//Create a context
		m_OALContext = alcCreateContext(m_OALDevice, NULL);

		//Set active context
		alcMakeContextCurrent(m_OALContext);
	}

}


void cSoundMgr::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cSoundMgr::add(LPCSTR sndName, LPCSTR fileName)
{
	if (!getSnd(sndName))
	{
		cSound * newSnd = new cSound();
		newSnd->loadWAVFile(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

cSound* cSoundMgr::getSnd(LPCSTR sndName)
{
	map<LPCSTR, cSound*>::iterator snd = gameSnds.find(sndName);
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}


LPCSTR cSoundMgr::getHitSnd()
{
	int size = hitSoundList.size();
	if (rand() % 2 == 0)
		return hitSoundList[(rand() % size)];
	else
		return hitSoundList[(size-1)];
}




void cSoundMgr::deleteSnd()
{
	for (map<LPCSTR, cSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}


void cSoundMgr::updateSound()
{
	


	switch (gameScreen)
	{
	case intro:
		switchSound("BGM6-intro");
		break;
	case guide:
		break;
	case game:

		if (firstCall)
		{
			currentSnd = getSnd("BGM1");
			currentSnd->playAudio(AL_LOOPING);
			firstCall = false;
		};

		if (m_InputMgr->isKeyDown(VK_NUMPAD1))
		{
			switchSound("BGM1");
		};
		if (m_InputMgr->isKeyDown(VK_NUMPAD2))
		{
			switchSound("BGM2");
		};

		if (m_InputMgr->isKeyDown(VK_NUMPAD3))
		{
			switchSound("BGM3");
		};

		if (m_InputMgr->isKeyDown(VK_NUMPAD4))
		{
			switchSound("BGM4");
		};

		if (m_InputMgr->isKeyDown(VK_NUMPAD5))
		{
			switchSound("BGM5");
		};

		if (m_InputMgr->isKeyDown(VK_NUMPAD0))
		{
			currentSnd->stopAudio();
		};

		break;
	case gameOver:
		switchSound("BGM7-endGame");
		break;
	default:
		break;
	}
	





}


void cSoundMgr::switchSound(LPCSTR sndName)
{
	cSound *newsound = getSnd(sndName);
	if (newsound != currentSnd)
	{
		if (currentSnd != NULL)
		{
			currentSnd->stopAudio();
		}

		currentSnd = getSnd(sndName);
		currentSnd->playAudio(AL_LOOPING);
	}
	else
	{
		if (currentSnd->isPlaying == false)
		{
			currentSnd->playAudio(AL_LOOPING);
		}
	}
}

cSoundMgr::~cSoundMgr()
{
	m_OALContext = alcGetCurrentContext();

	//Get device for active context
	m_OALDevice = alcGetContextsDevice(m_OALContext);

	//Release context(s)
	alcDestroyContext(m_OALContext);

	//Close device
	alcCloseDevice(m_OALDevice);

}
