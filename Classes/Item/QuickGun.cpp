#include "QuickGun.h"

bool QuickGun::init()
{
	Sprite* pSprite = Sprite::create("item/quickGun.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	bindSprite(pSprite);
	m_type = 1;
	//setDamage(1);
	return true;
}

Bullet* QuickGun::createBullet()
{
	Bullet* pBullet = QuickGunBullet::create();

	if (IsEffect)
		AudioEngine::play2d("Audio/fx_shotgun.mp3");
	return pBullet;
}