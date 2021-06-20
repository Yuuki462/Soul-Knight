#ifndef _SWORD_H_
#define _SWORD_H_

#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include "Item/Weapon.h"
#include "Scene/PauseMenu.h"
using namespace cocos2d;

class Sword :public Weapon
{
public:
	CREATE_FUNC(Sword)
	Bullet* createBullet() override;

	void bindsprite(Sprite* sprite);

	//void update(float delta) override;以后可能有用
	
	bool init() override;

protected:

	Vector<SpriteFrame*>m_rightActionVec;
	Vector<SpriteFrame*>m_leftActionVec;
	bool face;
	Sprite* mysword;
	int damage=4;

};
#endif