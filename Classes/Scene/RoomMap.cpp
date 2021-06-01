#include "RoomMap.h"

Scene* RoomMap::createScene(TMXTiledMap* map)
{
    auto scene = Scene::create();
    auto layer = RoomMap::create(map);
    scene->addChild(layer);
    return scene;
}
RoomMap* RoomMap::create(TMXTiledMap* map)
{
    auto* pRet = new(std::nothrow) RoomMap(map);
    if (pRet)
    {
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
    }
    delete pRet;
    pRet = nullptr;
    return nullptr;
}
bool RoomMap::init()
{
    if (!Scene::init())
    {
        return false;
    }

    if (m_pMap == nullptr)
    {
        log("tile map not found");
    }
    else
    {
        m_pMap->setAnchorPoint(Vec2::ZERO);
        m_pMap->setPosition(Vec2(10, 10));
        this->addChild(m_pMap, 0, 99);
    }
    /*
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(RoomMap::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    */


    if (m_mapNumber == 1)
    {
        /*
        auto dm1 = createMonsterRand();

        dm1->setPosition(500, 370);
        this->addChild(dm1, 9, sk::tag::kMonster);
        */

    }
   // this->scheduleUpdate();

    return true;
}
TMXTiledMap* RoomMap::createTiled(int mapNumber)
{
    if (mapNumber == 1) return TMXTiledMap::create("map/BirthRoom.tmx");
    return nullptr;
}

