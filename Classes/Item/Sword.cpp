#include "Sword.h"
#include"cocos2d.h"
#include "Item/SwordBullet.h"

void Sword::bindsprite(Sprite* sprite)
{
	mysword = sprite;
}

Bullet* Sword::createBullet()
{
	auto begin = CallFunc::create([&]() {
		m_pSprite->setVisible(false);
		});
	auto delay = DelayTime::create(0.9);
	auto end = CallFunc::create([&]() {
		m_pSprite->setVisible(true);
		});
	auto seq = Sequence::create(begin, delay, end, nullptr);
	Bullet* pBullet = SwordBullet::create();
	m_pSprite->runAction(seq);

	if (IsEffect)
		AudioEngine::play2d("Audio/fx_sword.mp3");
	return pBullet;
}

bool Sword::init()
{
	Sprite* pSprite = Sprite::create("item/Sword.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	bindSprite(pSprite);
	m_type = 2;
	//setDamage(1);
	return true;
}


