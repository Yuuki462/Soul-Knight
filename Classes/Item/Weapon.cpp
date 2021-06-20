#include "Weapon.h"

Bullet* Weapon::createBullet()
{
	return nullptr;
}

Rect Weapon::getBox()
{
	return m_pSprite->getBoundingBox();
}

int Weapon::getDamage()
{
	return m_damage;
}
bool Weapon::checkAttack()
{
	return is_attack;
}

void Weapon::reinit()
{
	this->retain();
	this->removeFromParent();
	this->m_pInformation->setVisible(false);
}