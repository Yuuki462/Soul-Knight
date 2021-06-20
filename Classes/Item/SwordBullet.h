#ifndef _SWORDBULLET_H_
#define _SWORDBULLET_H_

#include "Bullet.h"
class SwordBullet :public Bullet {
public:
	CREATE_FUNC(SwordBullet);

	bool init() override;

	void attack(Point heroPoint, int curFacing, Vec2 monsterPos) override;

protected:

	Vector<SpriteFrame*> m_rightActionVec;
	Vector<SpriteFrame*> m_leftActionVec;

};
#endif