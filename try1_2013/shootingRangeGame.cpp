/*
==================================================================================
ShootingRangeGame.cpp
==================================================================================
*/

#include "shootingRangeGame.h"

vector<cEnemy*> theEnemy;
vector<cBullet*> theBullets;

int magazineSize;
int bulletsLeft;
bool autoFollowBullet;
int targetHitCount;
