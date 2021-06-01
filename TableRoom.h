#ifndef __TableRoom_H__
#define __TableRoom_H__

#include "cocos2d.h"
#include "player\Hero.h"
#include "Weapon/Sword.h"

USING_NS_CC;
class TableRoom : public Scene
{
public:
    static Scene* createScene();


    bool init() override;
    TMXObjectGroup* barrier;
   
    void update(float delta);
   

    void isCollision();

    // implement the "static create()" method manually
    CREATE_FUNC(TableRoom);
    int count=0;
protected:
    TMXTiledMap* m_pMap;
    Hero* hero;
};

#endif