#include "Spear.h"
#include"cocos2d.h"
#include "Item/SpearBullet.h"


void Spear::bindsprite(Sprite* sprite)
{
	myspear = sprite;
}
Bullet* Spear::createBullet()
{
	auto begin = CallFunc::create([&]() {
		m_pSprite->setVisible(false);
		});
	auto delay = DelayTime::create(0.9);
	auto end = CallFunc::create([&]() {
		m_pSprite->setVisible(true);
		});
	auto seq = Sequence::create(begin, delay, end, nullptr);
	Bullet* pBullet = SpearBullet::create();
	m_pSprite->runAction(seq);

	if (IsEffect)
		AudioEngine::play2d("Audio/fx_sword.mp3");
	return pBullet;
}
bool Spear::init()
{
	Sprite* pSprite = Sprite::create("item/Spear.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	bindSprite(pSprite);
	m_type = 3;
	return true;
}