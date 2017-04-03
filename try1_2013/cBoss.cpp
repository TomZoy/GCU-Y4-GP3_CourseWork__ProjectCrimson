#include "cBoss.h"

cBoss::cBoss() : cEnemy()
{
	maxHealthPoints = 100;
	healthPoints = maxHealthPoints;
	moovingSpeed = 10.0f; //THIS NEEDS TESTING
	fastMoovingSpeed = 25.0f; //THIS NEEDS TESTING
	bool doTeleport = false;
}

void cBoss::update(float elapsedTime)
{
	mdlDimensions tmp = {5.0f,5.0f,5.0f};
	cModel::setMdlDimensions(tmp);
	//float yPos = (cModel::m_mdlSpeed / 4) * elapsedTime;
	//cModel::m_mdlPosition.y += yPos;



	if (healthPoints <= 0) 	//check if dead
	{
		//play victory sound
		m_SoundMgr->getSnd("mario10Coin")->playAudio(AL_TRUE);
		gameScreen = gameOver;
	}
	else if (healthPoints < 11)
	{
		//shrink
		mdlDimensions tmp = { 1.0f, 1.0f, 1.0f };
		cModel::setMdlDimensions(tmp);
		setMdlRadius(1.0f);
 		setScale(glm::vec3(1.0f,1.0f,1.0f));

	}
	else if (healthPoints < 26)
	{
		//start teleporting
		doTeleport = true;
	}
	else if (healthPoints < 51)
	{
		//speed up
		moovingSpeed = fastMoovingSpeed;
	}
	else
	{

	}

	//move about + attack



}

cBoss::~cBoss()
{

}