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
	void move(float elapsedTime);
	vector<cBullet*> *theBulletList;
	bool isSpawTriggered;

	int debug;

	//switches for one-time sound triggering
	bool speedUpped;
	bool teleporting;
	bool shrinked;




public:
	cBoss();

	virtual void update(float elapsedTime);

	int healthPoints;
	int maxHealthPoints;

	bool enableAttack;

	void attachBulletList(vector<cBullet*> *theBullets);

	float moovingSpeed;
	float fastMoovingSpeed;
	bool doTeleport;

	void spawn(float elapsedTime);

	void startLevel();

	void Die();

	~cBoss();




};
#endif