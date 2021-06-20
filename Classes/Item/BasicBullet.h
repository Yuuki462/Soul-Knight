#ifndef _BASICBULLET_H_
#define _BASICBULLET_H_

#include "Bullet.h"

class BasicBullet :public Bullet {
public:
	CREATE_FUNC(BasicBullet);

	bool init() override;

	void attack(Point heroPoint, int curFacing, Vec2 monsterPos) override;

};

#endif
