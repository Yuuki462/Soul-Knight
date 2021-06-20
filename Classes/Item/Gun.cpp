#include "Gun.h"

bool Gun::init()
{
	Sprite* pSprite = Sprite::create("item/weapons.png");
	if (pSprite == nullptr)
	{
		log("weapons.png not found");
	}
	bindSprite(pSprite);
	//createBullet();
	
	//setDamage(1);
	return true;
}

Bullet* Gun::createBullet()
{
	Bullet* pBullet = BasicBullet::create();
	if (IsEffect)
		AudioEngine::play2d("Audio/fx_normal_gun.mp3");
	return pBullet;
}