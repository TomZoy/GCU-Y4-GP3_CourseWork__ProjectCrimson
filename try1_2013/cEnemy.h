#ifndef _CENEMIES_H
#define _CENEMIES_H

#include "GameConstants.h"
#include "cModel.h"

class cEnemy : public cModel
{
public:
	cEnemy();
	int ID;

	void randomise(int xRange, int yRange, int zRange);
	virtual void update(float elapsedTime);


	~cEnemy();

private:
	const float m_EnemyMinSpeed = 3.0f;
	const float m_EnemyMaxSpeed = 6.0f;
	const float m_EnemySpeedAdjustment = 2.5f;

};
#endif