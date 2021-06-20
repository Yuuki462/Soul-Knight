#ifndef __BoxRoom_H__
#define __BoxRoom_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class BoxRoom : public Scene
{
public:
	//CREATE_FUNC(BoxRoom);

	virtual bool init();

	static BoxRoom* create();
};


#endif