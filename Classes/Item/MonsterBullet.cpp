#include "MonsterBullet.h"

bool MonsterBullet::init()
{
	Sprite* pSprite = Sprite::create("item/bullets/bullet_square.png");
	if (pSprite == nullptr)
	{
		log("bullet.png not found");
	}
	bindSprite(pSprite);
	return true;
}

void MonsterBullet::attack(Point heroPoint, int curFacing, Vec2 pos)
{
	heroPoint.x += 25.0;
	heroPoint.y += 20.0;
	m_pBulletSprite->setPosition(heroPoint);
	auto v = Vec2(random(-100, 100), random(-100, 100));
	v.normalize();
	v *= 2000;
	auto actionMove = MoveTo::create(9.5f, v);
	auto actionRemove = RemoveSelf::create();
	/*m_pBulletSprite->runAction(Sequence::create(actionMove, actionRemove, nullptr));*/
	m_pBulletSprite->runAction(Sequence::create(actionMove, nullptr));
}

bool BossBullet::init()
{
	Sprite* pSprite = Sprite::create("item/bullets/Monster_bullet_2.png");
	if (pSprite == nullptr)
	{
		log("bullet.png not found");
	}
	bindSprite(pSprite);
	return true;
}