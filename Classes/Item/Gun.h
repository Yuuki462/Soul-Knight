#ifndef _GUN_H_
#define _GUN_H_

#include "Weapon.h"
#include "BasicBullet.h"
#include "Scene/PauseMenu.h"
using namespace cocos2d;

class Gun :public Weapon
{
public:
	Bullet* createBullet() override;

	bool init() override;

	CREATE_FUNC(Gun);

};
#endif
