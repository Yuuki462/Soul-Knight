#ifndef __TableRoom_H__
#define __TableRoom_H__

#include "cocos2d.h"
#include "Scene/BulletLayer.h"

USING_NS_CC;
class TableRoom : public Scene
{
public:

    static Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(Ref* pSender);
    //bool onContactBegin(PhysicsContact& contact);
    // implement the "static create()" method manually
    CREATE_FUNC(TableRoom);


};

#endif