/**
*@file   HeroUI.cpp
*@author Р¤Со
*@date   6/14/2020
*/

#include "HeroUI.h"

void HeroUI::present(Hero*_hero)
{
	bindhero(_hero);
	m_pSprite = Sprite::create("item/ui/ui_board.png");
	this->addChild(m_pSprite, 1);
	
	m_presentHP = m_pHero->getBlood_v();
	m_presentArmor = m_pHero->getShield();
	//m_presntCoin = m_pHero->m_coinNumber;

	m_pHealth = ProgressTimer::create(Sprite::create("item/ui/ui_health_bar.png"));
	m_pHealth->setPosition(16.5f, 33.f);
	m_pHealth->setType(ProgressTimer::Type::BAR);
	m_pHealth->setMidpoint(Point(0, 0.5));
	m_pHealth->setBarChangeRate(Point(1, 0));
	m_pHealth->setPercentage(static_cast<float>(m_pHero->getBlood_v())
		/ static_cast<float>(m_pHero->maxblood) * 100);
	this->addChild(m_pHealth, 2);

	m_pArmor = ProgressTimer::create(Sprite::create("item/ui/ui_armor_bar.png"));
	m_pArmor->setPosition(16.5f, 3.f);
	m_pArmor->setType(ProgressTimer::Type::BAR);
	m_pArmor->setMidpoint(Point(0, 0.5));
	m_pArmor->setBarChangeRate(Point(1, 0));
	m_pArmor->setPercentage(static_cast<float>(m_pHero->getShield())
		/ static_cast<float>(m_pHero->maxshield) * 100);
	this->addChild(m_pArmor, 2);

	std::string healthMessage = std::to_string(m_pHero->blood_v) + "/" +
		std::to_string(m_pHero->maxblood);
	m_pHealthMessage = Label::createWithTTF(healthMessage, "Font/IRANYekanBold.ttf", 18.f);
	m_pHealthMessage->setPosition(16.5f, 33.f);
	this->addChild(m_pHealthMessage, 3);
	

	std::string armorMessage = std::to_string(m_pHero->shield) + "/" +
		std::to_string(m_pHero->maxshield);
	m_pArmorMessage = Label::createWithTTF(armorMessage, "Font/IRANYekanBold.ttf", 18.f);
	m_pArmorMessage->setPosition(16.5f, 3.f);
	this->addChild(m_pArmorMessage, 3);

	/*
	std::string coinMessage = std::to_string(m_pHero->m_coinNumber);
	m_pCoinMessage = Label::createWithTTF(coinMessage, "Font/IRANYekanBold.ttf", 18.f);
	m_pCoinMessage->setPosition(8.f, -27.f);
	this->addChild(m_pCoinMessage, 3);
	*/
	schedule(CC_SCHEDULE_SELECTOR(HeroUI::scheduleUI), 0.1f);

}

void HeroUI::scheduleUI(float dt)
{
	if (m_pHero->blood_v != m_presentHP)
	{
		m_presentHP = m_pHero->blood_v;
		m_pHealth->setPercentage(static_cast<float>(m_pHero->blood_v)
			/ static_cast<float>(m_pHero->maxblood) * 100);
		std::string healthMessage = std::to_string(m_pHero->blood_v) + "/" +
			std::to_string(m_pHero->maxblood);
		m_pHealthMessage->setString(healthMessage);
		
	}

	if (m_pHero->shield != m_presentArmor)
	{
		m_presentArmor = m_pHero->shield;
		m_pArmor->setPercentage(static_cast<float>(m_pHero->shield)
			/ static_cast<float>(m_pHero->maxshield) * 100);
		std::string armorMessage = std::to_string(m_pHero->shield) + "/" +
			std::to_string(m_pHero->maxshield);
		m_pArmorMessage->setString(armorMessage);
	}
	/*
	if (m_pHero->m_coinNumber != m_presntCoin)
	{
		m_presntCoin = m_pHero->m_coinNumber;
		std::string coinMessage = std::to_string(m_pHero->m_coinNumber);
		m_pCoinMessage->setString(coinMessage);
	}
	*/
}

void HeroUI::bindhero(Hero*_hero)
{
	m_pHero = _hero;
}