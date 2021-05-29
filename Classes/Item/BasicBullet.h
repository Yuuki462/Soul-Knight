#ifndef _BASICBULLET_H_
#define _BASICBULLET_H_

#include "Bullet.h"

class BasicBullet :public Bullet {
public:
	CREATE_FUNC(BasicBullet);

	bool init() override;

	void attack(float mouseX, float mouseY, Point heroPoint, int curFacing, Node* p_sprite) override;
};

#endif
