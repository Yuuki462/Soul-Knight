#ifndef _SPEARBULLET_H_
#define _SPEARBULLET_H_

#include "Bullet.h"
class SpearBullet :public Bullet {
public:
	CREATE_FUNC(SpearBullet);

	bool init() override;

	void attack(Point heroPoint, int curFacing, Vec2 monsterPos) override;

protected:

	Vector<SpriteFrame*> m_rightActionVec;
	Vector<SpriteFrame*> m_leftActionVec;

};
#endif