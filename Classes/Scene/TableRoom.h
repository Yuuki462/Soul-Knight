#ifndef __TableRoom_H__
#define __TableRoom_H__

#include <vector>
#include "cocos2d.h"
#include "Item/Weapon.h"

#include "player\Hero.h"
#include "Item/BasicBullet.h"
#include "Item/SwordBullet.h"
#include "Monster\monster.h"
#include "Scene/BoxRoom.h"
USING_NS_CC;
class TableRoom : public Scene
{
public:

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    static Scene* createScene();
    virtual bool init();
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    void update(float delta)override;
    //bool onContactBegin(PhysicsContact& contact);
    // implement the "static create()" method manually
    CREATE_FUNC(TableRoom);
    Sprite* transfer;
    Hero* hero;
    void startgame();
    void isCollision();
    TMXTiledMap* m_pMap;
    TMXObjectGroup* barrier;
    //BulletLayer* bulletLayer;
    Vector<Bullet*> m_vBullet;
};

#endif