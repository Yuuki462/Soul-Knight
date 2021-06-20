#include "Treasure.h"

static const std::string TreasureInformation = "get an unknown item";

bool Treasure::init()
{
	m_pSprite = Sprite::create("item/treasure_closed.png");
	m_pSprite->setPosition(600,400);
	this->addChild(m_pSprite);
	m_pInformation = showInformation(TreasureInformation);
	m_pInformation->setPosition(600, 350);
	this->addChild(m_pInformation);
	return true;
}

int Treasure::open()
{
	int num =  random(1,6);
	return num;
}