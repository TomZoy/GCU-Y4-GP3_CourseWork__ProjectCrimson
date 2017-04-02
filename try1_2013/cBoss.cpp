#include "cBoss.h"

cBoss::cBoss() : cEnemy()
{

	healthPoints = 100;
}

void cBoss::update(float elapsedTime)
{
	//float yPos = (cModel::m_mdlSpeed / 4) * elapsedTime;
	//cModel::m_mdlPosition.y += yPos;
}

cBoss::~cBoss()
{

}