#include "HealthPotion.h"

static const std::string HealthPotionInformation = "Health Potion";

bool HealthPotion::init()
{
	m_pSprite = Sprite::create("item/HealthPotion.png");
	m_pSprite->setPosition(600, 400);
	this->addChild(m_pSprite);
	m_pInformation = showInformation(HealthPotionInformation);
	m_pInformation->setPosition(600, 350);
	this->addChild(m_pInformation);
	return true;
}