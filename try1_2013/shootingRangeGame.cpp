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
bool allowBaloons;	//allow baloons to fly, once all targets are gone
bool perfectCombo; //perfect combo if all 6 targets are hit without reloading

float normalBulletSpeed;
float fastBulletSpeed = 50.0f;
float currentBulletSpeed = 5.0f;


int targetHitCount; //aka points



void enableBaloons()
{
	for (int loop = 0; loop < 10; loop++)
	{
		theBaloonList[loop]->setIsActive(true);
	}
}