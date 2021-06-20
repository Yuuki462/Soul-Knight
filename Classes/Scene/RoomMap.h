#ifndef __ROOMMAP_H__
#define __ROOMMAP_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "player/Hero.h"
#include "Monster/CloseMonster.h"
#include "player/HeroUI.h"
#include "Item/Gun.h"
#include "Item/BasicBullet.h"
#include "Item/SwordBullet.h"
#include "Monster/DistantMonster.h"
#include "Item/QuickGun.h"
#include "TableRoom.h"
#include "Scene/PauseMenu.h"
#include "Item/Treasure.h"
#include "Item/ArmorPotion.h"
#include "Item/HealthPotion.h"
#include "Item/Spear.h"
USING_NS_CC;
class RoomMap : public Scene
{
public:


    static Scene* createRoomScene(Hero*_hero,int num);

    virtual bool initScene(Hero*_hero,int num);

    void bindhero(Hero* hero1, Hero* hero2);//将hero1的数据传给hero2
    
    void addHero(Hero* _hero);

    void CheckCollition();

    CREATE_FUNC(RoomMap);

    void isCollision();

    void update(float delta)override;

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    Vec2 getMonsterPosition();

    void createMonster();

    void checkBullet();

    void generateDoor();

    void openDoor();

    void transScene();

    TMXTiledMap* createmap(int num);

    ValueMap getwallmap(std::string name);

    void MonsterCollition();


protected:
    TMXTiledMap* m_pMap;
    int mnum;
    Hero* hero;
    bool stopcheck1 = 0;
    bool stopcheck2 = 0;
    bool AttackOnce1 = 1;//一次攻击只能造成一次伤害
    bool AttackOnce2 = 1;
    Vector<Bullet*> m_vBullet;
    Vector<Monster*> m_vMonster;
    Vector<Sprite*> vecDoorOpen, vecDoorClose;
    bool is_attack = 0;
    Treasure* treasure;
    bool treasureOpen = false;
    Item* treasureItem;
    int treasureType;
    Sprite* treasureWeapon;//3~6为刀、矛、枪、快抢
    Sprite* door;
};

#endif 