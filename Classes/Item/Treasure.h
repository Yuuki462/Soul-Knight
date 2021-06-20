#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "Item/Item.h"
using namespace cocos2d;

class Treasure :public Item
{
public:
	CREATE_FUNC(Treasure)

	bool init() override;

	int open();



protected:
	Item* m_pUnknownItem;
};

#endif