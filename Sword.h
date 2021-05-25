#ifndef _SWORD_H_
#define _SWORD_H_

#include"cocos2d.h"
#include"ui/CocosGUI.h"

using namespace cocos2d;

class Sword :public Node
{
public:
	CREATE_FUNC(Sword)
	bool init();

	void bindsprite(Sprite* sprite);

	void attack(bool face);//¹¥»÷º¯Êý

protected:
	
	std::vector<bool>keypressed = std::vector<bool>(7, false);
	Vector<SpriteFrame*>m_rightActionVec;
	Vector<SpriteFrame*>m_leftActionVec;
	bool face;
	Sprite* mysword;
};
#endif