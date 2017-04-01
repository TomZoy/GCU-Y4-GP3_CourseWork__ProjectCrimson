#include "cPlayer.h"
#include "cCameraMgr.h"
#include "shootingRangeGame.h"

cPlayer::cPlayer() : cModel()
{
	magazineSize = 6;
	bulletsLeft = magazineSize;

	autoFollowBullet = true;
	firstMagazine = true;

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::attachCameraMgr(cCameraMgr* cameraMgr)
{
	theCameraMgr = cameraMgr;
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

	if (m_InputMgr->isKeyDown('F'))
	{
		if (autoFollowBullet)
		{
			autoFollowBullet = false;
		}
		else
		{
			autoFollowBullet = true;
		}
	}


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
		firstMagazine = false;
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
			theBullets.push_back(new cLaser);
			int numLasers = theBullets.size() - 1;
			theBullets[numLasers]->setDirection(mdlLaserDirection);
			theBullets[numLasers]->setRotation(0.0f);
			theBullets[numLasers]->setScale(glm::vec3(1, 1, 1));
			theBullets[numLasers]->setSpeed(5.0f);
			theBullets[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
			theBullets[numLasers]->setIsActive(true);
			//theBullets[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
			theBullets[numLasers]->update(elapsedTime);
			// play the firing sound
			m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
			*/

			/*bullet*/
			glm::vec3 mdlBulletDirection;
			mdlBulletDirection.x = 0.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
			mdlBulletDirection.y = 0.0f;// (float)glm::cos(glm::radians(this->getRotation()));
			mdlBulletDirection.z = 1.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
			//mdlBulletDirection *= -1;

			// Add new bullet sprite to the vector array
			theBullets.push_back(new cBullet);
			int numBullets = theBullets.size() - 1;
			theBullets[numBullets]->setDirection(mdlBulletDirection);
			theBullets[numBullets]->setRotation(90.0f);
			theBullets[numBullets]->setScale(glm::vec3(0.2f, 0.2f, 0.15f));
			theBullets[numBullets]->setSpeed(5.0f);//80.0f);
			theBullets[numBullets]->setPosition(glm::vec3(this->getPosition().x, this->getPosition().y + 0.5f, this->getPosition().z) + mdlBulletDirection);
			theBullets[numBullets]->setIsActive(true);
			theBullets[numBullets]->update(elapsedTime);
			theBullets[numBullets]->setMdlRadius(0.5f);

			// play the firing sound
			m_SoundMgr->getSnd("fireGunSFX")->playAudio(AL_TRUE);

			bulletsLeft--;

			


		}
		else
		{
			m_SoundMgr->getSnd("emptyGunSFX")->playAudio(AL_TRUE);
		}

	}

	//update camera2 position to follow the last bullet
	if (theBullets.size() > 0)
	{
		theCameraMgr->updateCameraPos("camera2", theBullets[theBullets.size() - 1]->getPosition());
	}

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor)
	{
		(*bulletIterartor)->update(elapsedTime);
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->SphereSphereCollision((*bulletIterartor)->getPosition(), (*bulletIterartor)->getMdlRadius()))
			{
				// if a collision set the bullet and target to false
				(*enemyIterator)->setIsActive(false);
				(*bulletIterartor)->setIsActive(false);
				// play the explosion sound.
				m_SoundMgr->getSnd(m_SoundMgr->getHitSnd())->playAudio(AL_TRUE); //"targetHitSFX")->playAudio(AL_TRUE);

				//reset the follow-camera
				theCameraMgr->updateCameraPos("camera2", theCameraMgr->getCamera("camera1")->getTheCameraPos());// glm::vec3(0.0f, 1.0f, 8.0f));
				theCameraMgr->setCurrentCamera("camera1");

				//add a point
				targetHitCount++;
			}
		}
	}



	vector<cBullet*>::iterator bulletIterartor = theBullets.begin();
	while (bulletIterartor != theBullets.end())
	{
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = theBullets.erase(bulletIterartor);
			//reset the follow-camera
			theCameraMgr->updateCameraPos("camera2", theCameraMgr->getCamera("camera1")->getTheCameraPos());//  glm::vec3(0.0f, 1.0f, 8.0f));
			theCameraMgr->setCurrentCamera("camera1");
		}
		else
		{
			++bulletIterartor;
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

	//check for perfect-combo
	if (firstMagazine && theEnemy.size() == 0)
	{
		perfectCombo = true;
	}

	if (theEnemy.size() == 0)
	{
		allowBaloons = true;
		enableBaloons();
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