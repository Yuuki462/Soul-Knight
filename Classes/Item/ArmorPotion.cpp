#include "ArmorPotion.h"

static const std::string ArmorPotionInformation = "Armor Potion";

bool ArmorPotion::init()
{
	m_pSprite = Sprite::create("item/ArmorPotion.png");
	m_pSprite->setPosition(600, 400);
	this->addChild(m_pSprite);
	m_pInformation = showInformation(ArmorPotionInformation);
	m_pInformation->setPosition(600, 350);
	this->addChild(m_pInformation);
	return true;
}