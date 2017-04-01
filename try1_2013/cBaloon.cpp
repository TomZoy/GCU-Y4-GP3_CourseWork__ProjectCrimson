#include "cBaloon.h"

cBaloon::cBaloon() : cEnemy()
{


}

void cBaloon::update(float elapsedTime)
{
	float yPos = (cModel::m_mdlSpeed /4) * elapsedTime;
	cModel::m_mdlPosition.y += yPos;
}

cBaloon::~cBaloon()
{

}