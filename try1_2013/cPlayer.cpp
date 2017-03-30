#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{
	magazineSize = 6;
	bulletsLeft = magazineSize;
}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::update(float elapsedTime)
{
	//if (m_InputMgr->isKeyDown('W'))
	//{
	//	translationX += 1.0f;
	//}
	//if (m_InputMgr->isKeyDown('S'))
	//{
	//	translationX -= 1.0f;
	//}


	if (m_InputMgr->isKeyDown('A'))
	{
		translationZ += 1.0f;
	}
	if (m_InputMgr->isKeyDown('D'))
	{
		translationZ -= 1.0f;
	}

	if (m_InputMgr->isKeyDown('R'))
	{
		bulletsLeft = magazineSize;
		m_SoundMgr->getSnd("reloadSFX")->playAudio(AL_TRUE);
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		if (bulletsLeft > 0)
		{
			/*laser*/
			/*
			glm::vec3 mdlLaserDirection;
			mdlLaserDirection.x = -(float)glm::sin(glm::radians(this->getRotation()));
			mdlLaserDirection.y = 0.0f;
			mdlLaserDirection.z = (float)glm::cos(glm::radians(this->getRotation()));
			mdlLaserDirection *= -1;

			// Add new bullet sprite to the vector array
			theTardisLasers.push_back(new cLaser);
			int numLasers = theTardisLasers.size() - 1;
			theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
			theTardisLasers[numLasers]->setRotation(0.0f);
			theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
			theTardisLasers[numLasers]->setSpeed(5.0f);
			theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
			theTardisLasers[numLasers]->setIsActive(true);
			//theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
			theTardisLasers[numLasers]->update(elapsedTime);
			// play the firing sound
			m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
			*/

			/*bullet*/
			glm::vec3 mdlBulletDirection;
			mdlBulletDirection.x = 0.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
			mdlBulletDirection.y = 0.0f;// (float)glm::cos(glm::radians(this->getRotation()));
			mdlBulletDirection.z = -(float)glm::sin(glm::radians(this->getRotation()));
			mdlBulletDirection *= -1;

			// Add new bullet sprite to the vector array
			theBullets.push_back(new cBullet);
			int numBullets = theBullets.size() - 1;
			theBullets[numBullets]->setDirection(mdlBulletDirection);
			theBullets[numBullets]->setRotation(90.0f);
			theBullets[numBullets]->setScale(glm::vec3(0.2f, 0.2f, 0.15f));
			theBullets[numBullets]->setSpeed(80.0f);
			theBullets[numBullets]->setPosition(glm::vec3(this->getPosition().x, this->getPosition().y + 0.5f, this->getPosition().z) + mdlBulletDirection);
			theBullets[numBullets]->setIsActive(true);
			theBullets[numBullets]->update(elapsedTime);
			// play the firing sound
			m_SoundMgr->getSnd("fireGunSFX")->playAudio(AL_TRUE);

			bulletsLeft--;
		}
		else
		{
			m_SoundMgr->getSnd("emptyGunSFX")->playAudio(AL_TRUE);
		}

	}

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
	{
		(*laserIterartor)->update(elapsedTime);
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				// if a collision set the bullet and spaceship to false
				(*enemyIterator)->setIsActive(false);
				(*laserIterartor)->setIsActive(false);
				// play the explosion sound.
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}
	}

	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();
	while (laserIterartor != theTardisLasers.end())
	{
		if ((*laserIterartor)->isActive() == false)
		{
			laserIterartor = theTardisLasers.erase(laserIterartor);
		}
		else
		{
			++laserIterartor;
		}
	}

	vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();
	while (enemyIterartor != theEnemy.end())
	{
		if ((*enemyIterartor)->isActive() == false)
		{
			enemyIterartor = theEnemy.erase(enemyIterartor);
		}
		else
		{
			++enemyIterartor;
		}
	}

	// Find out what direction we should be thrusting, using rotation.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = -(float)glm::sin(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = 0.0f;
	mdlVelocityAdd.z = -(float)glm::cos(glm::radians(m_mdlRotation));

	m_mdlRotation -= rotationAngle;

	mdlVelocityAdd *= translationZ;
	m_mdlDirection += mdlVelocityAdd;

	m_mdlPosition += m_mdlDirection * m_mdlSpeed *elapsedTime;
	m_mdlDirection *= 0.95f;

	rotationAngle = 0;
	translationZ = 0;
}

cPlayer::~cPlayer()
{

}