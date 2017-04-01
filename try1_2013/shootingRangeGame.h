#ifndef _SHOOTINGRANGEGAME_H
#define _SHOOTINGRANGEGAME_H

// ShootingRange Game headers
#include "cEnemy.h"
#include "cBullet.h"

extern vector<cEnemy*> theEnemy;
extern vector<cBullet*> theBullets;

extern int magazineSize;
extern int bulletsLeft;
extern bool autoFollowBullet;

#endif