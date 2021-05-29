#include "BasicBullet.h"

bool BasicBullet::init()
{
	Sprite* pSprite = Sprite::create("item/gunbullet.png");
	if (pSprite == nullptr)
	{
		log("gunbullet.png not found");
	}
	bindSprite(pSprite);
	m_isArrive = false;
	return true;
}

void BasicBullet::attack(float mouseX, float mouseY, Point heroPoint, int curFacing, Node* p_sprite)
{
	heroPoint.x += 25.0;
	heroPoint.y += 20.0;
	m_pBulletSprite->setPosition(heroPoint);

	auto v = Vec2(mouseX - heroPoint.x, mouseY - heroPoint.y);
	v.normalize();
	v *= 2000;
	auto actionMove = MoveTo::create(2.5f, v);
	auto actionRemove = RemoveSelf::create();
	m_pBulletSprite->runAction(Sequence::create(actionMove, actionRemove, nullptr));
	
}