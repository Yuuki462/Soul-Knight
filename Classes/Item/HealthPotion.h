#ifndef _HEALTH_POTION_H_
#define _HEALTH_POTION_H_

#include "Item/Item.h"
using namespace cocos2d;

class HealthPotion :public Item
{
public:
	CREATE_FUNC(HealthPotion)

	bool init() override;
};

#endif
