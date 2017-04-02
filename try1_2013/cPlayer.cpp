#include "cPlayer.h"
#include "cCameraMgr.h"
#include "shootingRangeGame.h"
#include "GameConstants.h"

cPlayer::cPlayer() : cModel()
{
	magazineSize = 6;
	bulletsLeft = magazineSize;

	autoFollowBullet = true;
	firstMagazine = true;


	float currentBulletSpeed = normalBulletSpeed;

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::attachCameraMgr(cCameraMgr* cameraMgr)
{
	theCameraMgr = cameraMgr;
}


void cPlayer::switchToBossMode()
{
	//make the rifle bigger
	setScale(glm::vec3(2, 2, 2));
	
	//increase the magazine size and reaload the rifle
	magazineSize = 30;
	bulletsLeft = magazineSize;
	currentBulletSpeed = fastBulletSpeed;

}


void cPlayer::update(float elapsedTime)
{

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
			theBullets[numBullets]->setSpeed(currentBulletSpeed);//80.0f);
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
	| Check for target collisions
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

	/*
	==============================================================
	| Check for baloon collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor)
	{
		(*bulletIterartor)->update(elapsedTime);
		for (vector<cBaloon*>::iterator baloonIterator = theBaloonList.begin(); baloonIterator != theBaloonList.end(); ++baloonIterator)
		{
			if ((*baloonIterator)->SphereSphereCollision((*bulletIterartor)->getPosition(), (*bulletIterartor)->getMdlRadius()))
			{
				//add a point
				targetHitCount++;

				// set the bullet to false
				(*bulletIterartor)->setIsActive(false);

				// play the apropriate sound.
				if (perfectCombo)
				{
					m_SoundMgr->getSnd("marioCoin")->playAudio(AL_TRUE);
					if (targetHitCount % 10 == 0)
						m_SoundMgr->getSnd("mario10Coin")->playAudio(AL_TRUE);
				}
				else
				{
					m_SoundMgr->getSnd("bounce")->playAudio(AL_TRUE);
					(*baloonIterator)->setIsActive(false);
				}

			}
		}
	}


	//removing used bullets
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

	//removing the destroyed targets
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

	//removing the destroyed baloons
	if (allowBaloons) //only check if baloons are already enabled in the first place
	{
		if (perfectCombo == false) //only remove hit baloons if player not did a perfect combo
		{
			vector<cBaloon*>::iterator baloonIterartor = theBaloonList.begin();
			while (baloonIterartor != theBaloonList.end())
			{
				if ((*baloonIterartor)->isActive() == false)
				{
					baloonIterartor = theBaloonList.erase(baloonIterartor);
				}
				else
				{
					++baloonIterartor;
				}
			}
		}
	}

	//check for perfect-combo
	if (firstMagazine && theEnemy.size() == 0)
	{
		perfectCombo = true;
	}

	//enable the baloons once all targets are gone
	if (theEnemy.size() == 0 && allowBaloons == false)
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