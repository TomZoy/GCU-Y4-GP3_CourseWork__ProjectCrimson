#ifndef _CBOSS_H
#define _CBOSS_H

#include "GameConstants.h"
#include "cModel.h"
#include "cEnemy.h"
#include "cBullet.h"


class cBoss : public cEnemy
{

private:
	void attack(float elapsedTime);
	void teleport();
	void move();
	vector<cBullet*> *theBulletList;

	int debug;



public:
	cBoss();

	virtual void update(float elapsedTime);

	int healthPoints;
	int maxHealthPoints;

	void attachBulletList(vector<cBullet*> *theBullets);

	float moovingSpeed;
	float fastMoovingSpeed;
	bool doTeleport;
	~cBoss();




};
#endif