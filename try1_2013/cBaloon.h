#ifndef _CBALOONS_H
#define _CBALOONS_H

#include "GameConstants.h"
#include "cModel.h"
#include "cEnemy.h"
//#include "shootingRangeGame.h"

class cBaloon : public cEnemy
{
public:
	cBaloon();
	int ID;

	virtual void update(float elapsedTime);
	~cBaloon();


};
#endif