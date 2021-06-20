#ifndef _SPEAR_H_
#define _SPEAR_H_
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "Item/Weapon.h"
#include "Scene/PauseMenu.h"
using namespace cocos2d;

class Spear : public Weapon
{
public:
	CREATE_FUNC(Spear)

	Bullet* createBullet() override;
	bool init()override;
	void bindsprite(Sprite* sprite);
protected:
	Vector<SpriteFrame*>m_rightActionVec;
	Vector<SpriteFrame*>m_leftActionVec;
	bool face;
	Sprite* myspear;
	int damage = 5;
};


#endif