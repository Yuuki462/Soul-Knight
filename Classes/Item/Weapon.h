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

	Rect getBox();

	int getDamage();

	bool checkAttack();

	int getType() { return m_type; };

	void reinit();
protected:
	bool is_attack = 0;
	int m_damage=3;
	int m_type = 0;
};

#endif