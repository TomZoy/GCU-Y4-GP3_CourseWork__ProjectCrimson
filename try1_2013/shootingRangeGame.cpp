/*
==================================================================================
ShootingRangeGame.cpp
==================================================================================
*/

#include "shootingRangeGame.h"

vector<cEnemy*> theEnemy;
vector<cBullet*> theBullets;
vector<cBaloon*> theBaloonList;

int magazineSize;
bool firstMagazine;
int bulletsLeft;
bool autoFollowBullet;
bool allowBaloons;
bool perfectCombo;

int targetHitCount;


void enableBaloons()
{
	for (int loop = 0; loop < 10; loop++)
	{
		theBaloonList[loop]->setIsActive(true);
	}
}