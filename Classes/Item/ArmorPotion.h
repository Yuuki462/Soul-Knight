#ifndef _ARMOR_POTION_H_
#define _ARMOR_POTION_H_

#include "Item/Item.h"
using namespace cocos2d;

class ArmorPotion :public Item
{
public:
	CREATE_FUNC(ArmorPotion)

	bool init() override;
};

#endif
