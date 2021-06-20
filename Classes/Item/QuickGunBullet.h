#ifndef _QUICKGUNBULLET_H_
#define _QUICKGUNBULLET_H_

#include "Bullet.h"

class QuickGunBullet :public Bullet {
public:
	CREATE_FUNC(QuickGunBullet);

	bool init() override;

	void attack(Point heroPoint, int curFacing, Vec2 monsterPos) override;

};

#endif