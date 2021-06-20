#include "QuickGunBullet.h"

bool QuickGunBullet::init()
{
	Sprite* pSprite = Sprite::create("item/shotgunbullet.png");
	pSprite->setScale(1.16);
	if (pSprite == nullptr)
	{
		log("bullet.png not found");
	}
	bindSprite(pSprite);
	return true;
}

void QuickGunBullet::attack(Point heroPoint, int curFacing, Vec2 monsterPos)
{
	heroPoint.x += 25.0;
	heroPoint.y += 20.0;
	m_pBulletSprite->setPosition(heroPoint);
	
	auto v = Vec2(monsterPos.x - heroPoint.x + 100, monsterPos.y - heroPoint.y + 100);
	if (monsterPos.x == 1)
		v = Vec2(-1, 0.26);
	if (monsterPos.x == -1)
		v = Vec2(1, 0.26);
	v.normalize();
	v *= 2000;
	auto actionMove = MoveTo::create(2.5f, v);
	auto actionRemove = RemoveSelf::create();
	/*m_pBulletSprite->runAction(Sequence::create(actionMove, actionRemove, nullptr));*/
	m_pBulletSprite->runAction(Sequence::create(actionMove, nullptr));
}