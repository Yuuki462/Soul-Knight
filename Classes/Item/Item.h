#ifndef _ITEM_H_
#define _ITEM_H_

#include"cocos2d.h"
using namespace cocos2d;

class Item :public Node
{
public:
	void bindSprite(Sprite* pSprite);

	Sprite* getSprite();

	//virtual void interact()=0;

protected:
	Sprite* m_pSprite;

	//int m_price;
};

#endif