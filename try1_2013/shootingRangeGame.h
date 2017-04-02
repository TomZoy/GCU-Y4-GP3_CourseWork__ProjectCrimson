#ifndef _SHOOTINGRANGEGAME_H
#define _SHOOTINGRANGEGAME_H

// ShootingRange Game headers
#include "cEnemy.h"
#include "cBullet.h"
#include "cBaloon.h"
#include "GameConstants.h"

extern vector<cEnemy*> theEnemy;
extern vector<cBaloon*> theBaloonList;
extern vector<cBullet*> theBullets;




void enableBaloons();

extern int magazineSize;
extern int bulletsLeft;
extern int targetHitCount;

extern bool autoFollowBullet;

extern bool allowBaloons;
extern bool perfectCombo;
extern bool firstMagazine;
extern bool isGameOver; //it's game over when all the baloons are gone

extern float normalBulletSpeed;
extern float fastBulletSpeed;
extern float currentBulletSpeed;

#endif