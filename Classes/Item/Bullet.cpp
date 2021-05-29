#include "Bullet.h"


void Bullet::setDamage(int damage)
{
    m_damage = damage;
}

int Bullet::getDamage()
{
    return m_damage;
}

void Bullet::bindSprite(Sprite* pSprite)
{
    m_pBulletSprite = pSprite;
    this->addChild(m_pBulletSprite, 3);
}

void attack(float mouseX, float mouseY, Point heroPoint, int curFacing,
    Node* p_sprite = nullptr)
{

}

