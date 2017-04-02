#ifndef _SHOOTINGRANGEGAME_H
#define _SHOOTINGRANGEGAME_H

// ShootingRange Game headers
#include "cEnemy.h"
#include "cBullet.h"
#include "cBaloon.h"
#include "cBoss.h"
#include "GameConstants.h"

extern vector<cEnemy*> theEnemy;
extern vector<cBaloon*> theBaloonList;
extern vector<cBullet*> theBullets;

extern cBoss *theBossPointer;




void enableBaloons();

extern int magazineSize;
extern int bulletsLeft;
extern int targetHitCount;

extern bool autoFollowBullet;

extern bool allowBaloons;
extern bool perfectCombo;
extern bool firstMagazine;

extern float normalBulletSpeed;
extern float fastBulletSpeed;
extern float currentBulletSpeed;

#endif