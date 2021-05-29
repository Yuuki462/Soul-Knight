#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
#include "Item.h"
#include "Bullet.h"
using namespace cocos2d;

class Weapon :public Item
{
public:

	virtual Bullet* createBullet() = 0;


protected:

	//int m_damage;
};

#endif