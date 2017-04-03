#include "cBoss.h"

cBoss::cBoss() : cEnemy()
{
	maxHealthPoints = 100;
	healthPoints = maxHealthPoints;
	moovingSpeed = 10.0f; //THIS NEEDS TESTING
	fastMoovingSpeed = 25.0f; //THIS NEEDS TESTING
	doTeleport = false;

	debug = 0;
}


void cBoss::attachBulletList(vector<cBullet*> *theBullets)
{
	theBulletList = theBullets;
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
		mdlDimensions tmp = { 2.0f, 2.0f, 2.0f };
		cModel::setMdlDimensions(tmp);
		setMdlRadius(2.5f);
 		setScale(glm::vec3(2.0f,2.0f,2.0f));

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

	debug++;
	if (debug % 300 == 0)
	{
		attack(elapsedTime);

	}



}


void cBoss::attack(float elapsedTime)
{
	//play attackSound
	m_SoundMgr->getSnd("mario10Coin")->playAudio(AL_TRUE);


	/*bullet*/
	glm::vec3 mdlBulletDirection;
	mdlBulletDirection.x = 0.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
	mdlBulletDirection.y = 0.0f;// (float)glm::cos(glm::radians(this->getRotation()));
	mdlBulletDirection.z = -1.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
	//mdlBulletDirection *= -1;

	// Add new bullet sprite to the vector array
	theBulletList->push_back(new cBullet);
	int numBullets = theBulletList->size() - 1;
	theBulletList->at(numBullets)->setDirection(mdlBulletDirection);
	theBulletList->at(numBullets)->setRotation(-90.0f);
	theBulletList->at(numBullets)->setScale(glm::vec3(0.2f, 0.2f, 0.15f));
	theBulletList->at(numBullets)->setSpeed(2.0f);
	theBulletList->at(numBullets)->setPosition(glm::vec3(this->getPosition().x, this->getPosition().y, this->getPosition().z-2.0f) + mdlBulletDirection);
	theBulletList->at(numBullets)->setIsActive(true);
	theBulletList->at(numBullets)->update(elapsedTime);
	theBulletList->at(numBullets)->setMdlRadius(0.5f);


}


void cBoss::teleport()
{
	if (doTeleport)
	{

	}

}
void cBoss::move()
{
	
}








cBoss::~cBoss()
{

}