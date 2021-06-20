#ifndef _ITEM_H_
#define _ITEM_H_

#include"cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;

class Item :public Node
{
public:
	CREATE_FUNC(Item);


	void bindSprite(Sprite* pSprite);

	Sprite* getSprite();

	ui::Scale9Sprite* showInformation(const std::string& message);

	void remove();

	void changeSprite(Sprite* _sprite);

	void setInformationUnvisible();

protected:
	Sprite* m_pSprite=nullptr;
	ui::Scale9Sprite* m_pInformation;

};

#endif