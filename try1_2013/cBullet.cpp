#include "cBullet.h"

cBullet::cBullet() : cModel()
{

}

void cBullet::update(float elapsedTime)
{
	cBullet::m_mdlPosition += cBullet::m_mdlDirection * cBullet::m_mdlSpeed * elapsedTime;
	if (cModel::m_mdlPosition.x > PLAYFIELDX ||
		cModel::m_mdlPosition.x < -PLAYFIELDX ||
		cModel::m_mdlPosition.z > PLAYFIELDZ ||
		cModel::m_mdlPosition.z < -PLAYFIELDZ)
		cModel::m_IsActive = false;

}

cBullet::~cBullet()
{

}
