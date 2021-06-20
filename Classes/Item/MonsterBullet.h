#ifndef _MONSTERBULLET_H_
#define _MONSTERBULLET_H_

#include "Bullet.h"

class MonsterBullet :public Bullet {
public:
	CREATE_FUNC(MonsterBullet);

	bool init() override;

	void attack(Point heroPoint, int curFacing, Vec2 pos) override;

};

class BossBullet :public MonsterBullet {
public:
	CREATE_FUNC(BossBullet);

	bool init() override;


};
#endif
