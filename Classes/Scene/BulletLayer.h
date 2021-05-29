#ifndef _BULLETLAYER_H_
#define _BULLETLAYER_H_
#include "cocos2d.h"
#include "Item/BasicBullet.h"
#include "player/Hero.h"

using namespace cocos2d;

class BulletLayer :public Layer
{
public:
	CREATE_FUNC(BulletLayer);

	bool BulletLayer::init();

	bool onMouseDown(Event* event);

	void bindHero(Hero* pHero);
//	static BulletLayer* getInstance();
//
//protected:
//	static BulletLayer* m_pPresentBulletLayer;


private:
	Hero* m_pHero = nullptr;
};

#endif