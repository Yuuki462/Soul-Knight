#ifndef _QUICKGUN_H_
#define _QUICKGUN_H_

#include "Weapon.h"
#include "QuickGunBullet.h"
#include "Scene/PauseMenu.h"
using namespace cocos2d;

class QuickGun :public Weapon
{
public:
	Bullet* createBullet() override;

	bool init() override;

	CREATE_FUNC(QuickGun);

protected:
	int damage = 2;
};
#endif
