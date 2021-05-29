#include "BulletLayer.h"

//BulletLayer* BulletLayer::m_pPresentBulletLayer = nullptr;

bool BulletLayer::init()
{
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(BulletLayer::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	/*m_pPresentBulletLayer = this;*/
	return true;
}

void BulletLayer::bindHero(Hero* pHero)
{
	m_pHero = pHero;
}

bool BulletLayer::onMouseDown(Event* event)
{
	auto e = dynamic_cast<EventMouse*>(event);
	auto pBullet = m_pHero->getWeapon()->createBullet();
	log("Cursor at: %f, %f", e->getCursorX(), e->getCursorY());
	log("  Hero at: %f, %f", m_pHero->getSprite()->getPosition().x, m_pHero->getSprite()->getPosition().y);
	this->addChild(pBullet);
	pBullet->attack(e->getCursorX(), e->getCursorY(), m_pHero->getSprite()->getPosition(), 1);
	

	return true;
}

//BulletLayer* BulletLayer::getInstance()
//{
//	return m_pPresentBulletLayer;
//}