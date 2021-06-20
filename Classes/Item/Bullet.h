#ifndef _BULLET_H_
#define _BULLET_H_

#include "Item.h"
using namespace cocos2d;

class Bullet :public Node
{
public:
	int Bullet::getDamage();

	void Bullet::setDamage(int damage);

	Sprite* Bullet::getSprite();

	void Bullet::bindSprite(Sprite* pSprite);

	virtual void attack(Point heroPoint, int curFacing, Vec2 monsterPos) = 0;

protected:
	Sprite* m_pBulletSprite;
	int m_damage;
	bool m_isArrive;
	float m_speed;
};

#endif