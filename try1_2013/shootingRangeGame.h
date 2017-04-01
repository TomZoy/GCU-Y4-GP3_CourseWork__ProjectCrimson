#ifndef _SHOOTINGRANGEGAME_H
#define _SHOOTINGRANGEGAME_H

// ShootingRange Game headers
#include "cEnemy.h"
#include "cBullet.h"
#include "cBaloon.h"

extern vector<cEnemy*> theEnemy;
extern vector<cBaloon*> theBaloonList;
extern vector<cBullet*> theBullets;

extern enum gameScreen_enum { intro, guide, game, gameOver };
extern gameScreen_enum gameScreen;


void enableBaloons();

extern int magazineSize;
extern int bulletsLeft;
extern int targetHitCount;

extern bool autoFollowBullet;

extern bool allowBaloons;
extern bool perfectCombo;
extern bool firstMagazine;
extern bool isGameOver; //it's game over when all the baloons are gone

#endif