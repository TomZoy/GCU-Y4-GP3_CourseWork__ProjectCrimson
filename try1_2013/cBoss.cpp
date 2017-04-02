#include "cBoss.h"

cBoss::cBoss() : cEnemy()
{

	healthPoints = 100;
}

void cBoss::update(float elapsedTime)
{
	mdlDimensions tmp = {5.0f,5.0f,5.0f};
	cModel::setMdlDimensions(tmp);
	//float yPos = (cModel::m_mdlSpeed / 4) * elapsedTime;
	//cModel::m_mdlPosition.y += yPos;
}

cBoss::~cBoss()
{

}