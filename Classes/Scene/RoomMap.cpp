//#include"TableRoom.h"
#include "RoomMap.h"
#include "Monster\monster.h"
#include "Item/Sword.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* RoomMap::createRoomScene(Hero* _hero, int num)
{
    RoomMap* scene = new RoomMap();
    if (scene && scene->initScene(_hero, num))
    {
        scene->autorelease();//自动清理内存
        //scene->initScene(_hero, num);
        return scene;
    }
    return nullptr;
}

bool RoomMap::initScene(Hero* _hero, int num)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mnum =num+1;
    m_pMap = createmap(num);
    generateDoor();
    if (m_pMap == nullptr)
    {
        log("map.png not found");
    }
    else
    {
        this->addChild(m_pMap, 0);
    }
    addHero(_hero);
    createMonster();
    HeroUI* testUI = HeroUI::create();
    testUI->present(hero);
    testUI->setPosition(118.5f, 661.5f);
    this->addChild(testUI, 5, 6);

    auto attackListener = EventListenerKeyboard::create();
    attackListener->onKeyPressed = CC_CALLBACK_2(RoomMap::onKeyPressed, this);
    attackListener->onKeyReleased = CC_CALLBACK_2(RoomMap::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(attackListener, this);
    //m_pMap->setPosition(Vec2(0, -50));
    //map->setPosition(origin.x + visibleSize.width / 2,
    //    origin.y + visibleSize.height/2);
    //this->addChild(m_pMap,1);
    this->scheduleUpdate();

    return true;

}
void RoomMap::addHero(Hero* _hero)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*if (_hero->getname() == "Knight")
    {
        auto gun = Gun::create();

        hero = Hero::create();
        this->addChild(hero, 4);
        hero->addChild(gun, 5);

        hero->createHero(Vec2(600, 600));
        
        hero->setWeapon(gun);

        //hero->bindsprite(phero);
        hero->RestAction();

        auto keyBoardListenerHero = EventListenerKeyboard::create();
        keyBoardListenerHero->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
        keyBoardListenerHero->onKeyReleased = CC_CALLBACK_2(Hero::onKeyreleased, hero);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListenerHero, this);

        hero->scheduleUpdate();
    }*/
    hero = Hero::create();
    this->addChild(hero, 4);
    hero->createHero(Vec2(600, 600));
    bindhero(_hero, hero);
    if (_hero->getWeapon()->getType() == 0)
    {

        auto gun = Gun::create();
        hero->addChild(gun, 5);
        hero->setWeapon(gun);

    }
    else if (_hero->getWeapon()->getType() == 1)
    {
        auto gun = QuickGun::create();
        hero->addChild(gun, 5);
        hero->setWeapon(gun);
    }
    else if (_hero->getWeapon()->getType() == 2)
    {
        auto sword = Sword::create();
        hero->addChild(sword, 5);
        hero->setWeapon(sword);
    }
    else if (_hero->getWeapon()->getType() == 3)
    {
        auto spear = Spear::create();
        hero->addChild(spear, 5);
        hero->setWeapon(spear);
    }
    hero->RestAction();
    auto keyBoardListenerHero = EventListenerKeyboard::create();
    keyBoardListenerHero->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
    keyBoardListenerHero->onKeyReleased = CC_CALLBACK_2(Hero::onKeyreleased, hero);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListenerHero, this);
    hero->scheduleUpdate();
}

void RoomMap::bindhero(Hero* hero1, Hero* hero2)
{
    hero2->setname(hero1->getname());
    hero2->setBlood(hero1->getBlood_v());
    hero2->setshield(hero1->getShield());
    hero2->setcoin(hero1->getcoin());
    hero2->setSpeed(hero1->getSpeed());
    hero2->setWeapon(hero1->getWeapon());
    hero2->setMaxShield(hero1->getMaxShield());
}
//检测刀与怪物的碰撞
void RoomMap::CheckCollition()
{
    auto actionRemove = RemoveSelf::create();
    if ((hero->getWeapon()->getType() == 3||hero->getWeapon()->getType() == 2) && is_attack)
    {
        for (int i = 0; i < m_vMonster.size(); i++)
        {

            if (hero->getWeapon()->getSprite()->getBoundingBox().intersectsRect(m_vMonster.at(i)->getBox()) && AttackOnce1 == 1)
            {
                AttackOnce1 = 0;
                m_vMonster.at(i)->beingAttack();
                if (!m_vMonster.at(i)->checkalive())
                {
                    m_vMonster.at(i)->getSprite()->runAction(actionRemove);
                    m_vMonster.at(i)->removeAllChildrenWithCleanup(true);
                    m_vMonster.eraseObject(m_vMonster.at(i));
                }
            }

        }
    }
    if (!is_attack)
        AttackOnce1 = 1;
    

}

void RoomMap::update(float delta)
{
    if (hero->checkalive())
    {
        CheckCollition();
        checkBullet();
        isCollision();
        MonsterCollition();
        if (m_vMonster.size() == 0)
        {
            if (vecDoorOpen.size() == 0)
                openDoor();
            transScene();
            if (treasure == nullptr)
            {
                treasure = Treasure::create();
                this->addChild(treasure, 3);
            }
            if (mnum == 7)
            {
                
                if (door==nullptr)
                {
                    door = Sprite::create("map/transfergate.png");
                    door->setPosition(Vec2(600, 500));
                    this->addChild(door, 4);
                }
                if (door != nullptr)
                {
                    if (door->getBoundingBox().containsPoint(hero->getSprite()->getPosition()))
                    {
                        Director::getInstance()->replaceScene(TableRoom::create());
                    }
                }
            }
        }
    }
    else
        Director::getInstance()->pushScene(DieMenu::create());
}
ValueMap RoomMap::getwallmap(std::string name)
{
    TMXObjectGroup* wall;
    wall = m_pMap->getObjectGroup(name);
    ValueVector object = wall->getObjects();
    Value obj = object.at(0);
    ValueMap map = obj.asValueMap();
    return map;
}
void RoomMap::isCollision()
{
    Vec2 pos = hero->getposition();
    ValueMap map1, map2, map3;
    map1 = getwallmap("wall1");
    map2 = getwallmap("wall2");
    map3 = getwallmap("wall3");

    int x1 = map1.at("x").asInt();
    int y1 = map1.at("y").asInt();
    int width1 = map1.at("width").asInt();
    int height1 = map1.at("height").asInt();
    int x2 = x1 + width1;
    int y2 = y1 + height1;

    int x21 = map2.at("x").asInt();
    int y21 = map2.at("y").asInt();
    int width2 = map2.at("width").asInt();
    int height2 = map2.at("height").asInt();
    int x22 = x21 + width2;
    int y22 = y21 + height2;

    int x31 = map3.at("x").asInt();
    int y31 = map3.at("y").asInt();
    int width3 = map3.at("width").asInt();
    int height3 = map3.at("height").asInt();
    int x32 = x31 + width3;
    int y32 = y31 + height3;
    if (pos.x < x2 && pos.x>x2 - 56 && pos.y >= y1 && pos.y <= y2)
    {
        hero->setbanmove(3);//不能朝右
    }
    else if (pos.x > x1 && pos.x < x1 + 42 && pos.y >= y1 && pos.y <= y2)
    {
        hero->setbanmove(2);//不能朝左
    }
    else if (pos.y > y1 && pos.y < y1 + 28 && pos.x >= x1 && pos.x <= x2)
    {
        hero->setbanmove(1);//不能朝上
    }
    else if (pos.y < y2 && pos.y> y2 - 84 && pos.x >= x1 && pos.x <= x2)
    {
        hero->setbanmove(0);//不能朝下
    }

    else if (pos.x < x21 && pos.x>x21 - 42 && pos.y >= y21 && pos.y <= y22)
    {
        hero->setbanmove(3);//不能朝右
    }
    else if (pos.x > x22 && pos.x < x22 + 28 && pos.y >= y21 && pos.y <= y22)
    {
        hero->setbanmove(2);//不能朝左
    }
    else if (pos.y < y22 && pos.y> y22 + 28 && pos.x >= x21 && pos.x <= x22)
    {
        hero->setbanmove(1);//不能朝上
    }
    else if (pos.y < y21 && pos.y> y21 - 70 && pos.x >= x21 && pos.x <= x22)
    {
        hero->setbanmove(0);//不能朝下   
    }

    else if (pos.x < x31 && pos.x>x31 - 42 && pos.y >= y21 && pos.y <= y32)
    {
        hero->setbanmove(3);//不能朝右
    }
    else if (pos.x > x32 && pos.x < x32 + 28 && pos.y >= y31 && pos.y <= y32)
    {
        hero->setbanmove(2);//不能朝左
    }
    else if (pos.y < y31 && pos.y> y31 + 42 && pos.x >= x31 && pos.x <= x32)
    {
        hero->setbanmove(1);//不能朝上
    }
    else if (pos.y < y31 && pos.y> y31 - 70 && pos.x >= x31 && pos.x <= x32)
    {
        hero->setbanmove(0);//不能朝下
    }
    else
    {
        hero->setbanmove(4);//无禁止
    }



    //if (pos.x < x2 && pos.x>x2 - 56 && pos.y >= y1 && pos.y <= y2 || pos.x < x22 && pos.x>x22 - 56 && pos.y >= y21 && pos.y <= y22 || pos.x < x32 && pos.x>x32 - 56 && pos.y >= y31 && pos.y <= y32)
    //{
    //    hero->setbanmove(3);//不能朝右
    //}
    //else if (pos.x > x1 && pos.x < x1 + 42 && pos.y >= y1 && pos.y <= y2 || pos.x > x21 && pos.x < x21 + 42 && pos.y >= y21 && pos.y <= y22 || pos.x > x31 && pos.x < x31 + 42 && pos.y >= y31 && pos.y <= y32)
    //{
    //    hero->setbanmove(2);//不能朝左
    //}
    //else if (pos.y < y2 && pos.y> y2 - 84 && pos.x >= x1 && pos.x <= x2 || pos.y < y22 && pos.y> y22 - 84 && pos.x >= x21 && pos.x <= x22 || pos.y < y32 && pos.y> y32 - 84 && pos.x >= x31 && pos.x <= x32)
    //{
    //    hero->setbanmove(0);//不能朝下   
    //}
    //else if (pos.y > y1 && pos.y < y1 + 28 && pos.x >= x1 && pos.x <= x2 || pos.y > y21 && pos.y < y21 + 28 && pos.x >= x21 && pos.x <= x22 || pos.y > y31 && pos.y < y31 + 28 && pos.x >= x31 && pos.x <= x32)
    //{
    //    hero->setbanmove(1);//不能朝上
    //}
    //else
    //    hero->setbanmove(4);//无禁止
}

void RoomMap::MonsterCollition()
{
    for (int i = 0; i < m_vMonster.size(); i++)
    {
        {
            Vec2 pos = m_vMonster.at(i)->getposition();
            ValueMap map1, map2, map3;
            map1 = getwallmap("wall1");
            map2 = getwallmap("wall2");
            map3 = getwallmap("wall3");

            int x1 = map1.at("x").asInt();
            int y1 = map1.at("y").asInt();
            int width1 = map1.at("width").asInt();
            int height1 = map1.at("height").asInt();
            int x2 = x1 + width1;
            int y2 = y1 + height1;

            int x21 = map2.at("x").asInt();
            int y21 = map2.at("y").asInt();
            int width2 = map2.at("width").asInt();
            int height2 = map2.at("height").asInt();
            int x22 = x21 + width2;
            int y22 = y21 + height2;

            int x31 = map3.at("x").asInt();
            int y31 = map3.at("y").asInt();
            int width3 = map3.at("width").asInt();
            int height3 = map3.at("height").asInt();
            int x32 = x31 + width3;
            int y32 = y31 + height3;
            if (pos.x < x2 && pos.x>x2 - 56 && pos.y >= y1 && pos.y <= y2)
            {
                m_vMonster.at(i)->setbanmove(3);//不能朝右
            }
            else if (pos.x > x1 && pos.x < x1 + 42 && pos.y >= y1 && pos.y <= y2)
            {
                m_vMonster.at(i)->setbanmove(2);//不能朝左
            }
            else if (pos.y > y1 && pos.y < y1 + 28 && pos.x >= x1 && pos.x <= x2)
            {
                m_vMonster.at(i)->setbanmove(1);//不能朝上
            }
            else if (pos.y < y2 && pos.y> y2 - 84 && pos.x >= x1 && pos.x <= x2)
            {
                m_vMonster.at(i)->setbanmove(0);//不能朝下
            }

            else if (pos.x < x21 && pos.x>x21 - 42 && pos.y >= y21 && pos.y <= y22)
            {
                m_vMonster.at(i)->setbanmove(3);//不能朝右
            }
            else if (pos.x > x22 && pos.x < x22 + 28 && pos.y >= y21 && pos.y <= y22)
            {
                m_vMonster.at(i)->setbanmove(2);//不能朝左
            }
            else if (pos.y < y22 && pos.y> y22 + 28 && pos.x >= x21 && pos.x <= x22)
            {
                m_vMonster.at(i)->setbanmove(1);//不能朝上
            }
            else if (pos.y < y21 && pos.y> y21 - 70 && pos.x >= x21 && pos.x <= x22)
            {
                m_vMonster.at(i)->setbanmove(0);//不能朝下   
            }

            else if (pos.x < x31 && pos.x>x31 - 42 && pos.y >= y21 && pos.y <= y32)
            {
                m_vMonster.at(i)->setbanmove(3);//不能朝右
            }
            else if (pos.x > x32 && pos.x < x32 + 28 && pos.y >= y31 && pos.y <= y32)
            {
                m_vMonster.at(i)->setbanmove(2);//不能朝左
            }
            else if (pos.y < y31 && pos.y> y31 + 42 && pos.x >= x31 && pos.x <= x32)
            {
                m_vMonster.at(i)->setbanmove(1);//不能朝上
            }
            else if (pos.y < y31 && pos.y> y31 - 70 && pos.x >= x31 && pos.x <= x32)
            {
                m_vMonster.at(i)->setbanmove(0);//不能朝下
            }
            else
            {
                m_vMonster.at(i)->setbanmove(4);//无禁止
            }
        }
    }
}

void RoomMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
;
    if (keyCode == EventKeyboard::KeyCode::KEY_J&&hero->checkalive()&&hero!=nullptr)
    {
        is_attack = 1;
        auto pBullet = hero->getWeapon()->createBullet();
        m_vBullet.pushBack(pBullet);
        this->addChild(pBullet, 10);
        //if (pig->checkalive() && pig != nullptr)
        pBullet->attack(hero->getposition()+hero->getPosition(), hero->getis_turn(), getMonsterPosition());
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_L&&treasure!=nullptr)
    {
        if (hero->getSprite()->getBoundingBox().intersectsRect(treasure->getSprite()->getBoundingBox()) && !treasureOpen)
        {
            treasureType = treasure->open();
            treasure->getSprite()->setVisible(false);
            Sprite* _Sprite = Sprite::create("Item/treasure_opened.png");
            _Sprite->setPosition(Vec2(600, 400));
            this->addChild(_Sprite, 2);
            if (treasureType == 1)
            {
                treasureItem = HealthPotion::create();
                treasureWeapon = treasureItem->getSprite();
                this->addChild(treasureItem, 3);
            }
            else if (treasureType == 2)
            {
                treasureItem = ArmorPotion::create();
                treasureWeapon = treasureItem->getSprite();
                this->addChild(treasureItem, 3);
            }
            else if (treasureType == 3)
            {
                treasureWeapon = Sprite::create("item/Sword.png");
                treasureWeapon->setPosition(Vec2(600, 400));
                treasureItem = Item::create();
                this->addChild(treasureItem, 3);
                treasureItem->changeSprite(treasureWeapon);
                this->addChild(treasureWeapon, 3);
            }
            else if (treasureType == 4)
            {
                treasureWeapon = Sprite::create("item/spear.png");
                treasureWeapon->setPosition(Vec2(600, 400));
                treasureItem = Item::create();
                this->addChild(treasureItem, 3);
                treasureItem->changeSprite(treasureWeapon);
                this->addChild(treasureWeapon, 3);
            }
            else if (treasureType == 5)
            {
                treasureWeapon = Sprite::create("item/weapons.png");
                treasureWeapon->setPosition(Vec2(600, 400));
                treasureItem = Item::create();
                this->addChild(treasureItem, 3);
                treasureItem->changeSprite(treasureWeapon);
                this->addChild(treasureWeapon, 4);
            }
            else if (treasureType == 6)
            {
                treasureWeapon = Sprite::create("item/quickGun.png");
                treasureWeapon->setPosition(Vec2(600, 400));
                treasureItem = Item::create();
                this->addChild(treasureItem, 3);
                treasureItem->changeSprite(treasureWeapon);
                this->addChild(treasureWeapon, 4);
            }
            treasureOpen = true;
            treasure->setInformationUnvisible();
        }
        else if (treasureOpen && hero->getSprite()->getBoundingBox().intersectsRect(treasureItem->getSprite()->getBoundingBox())&& treasureType != 0)
        {
            if (treasureType == 1)
            {
                treasureItem->getSprite()->setVisible(false);
                treasureItem->setInformationUnvisible();
                hero->recoverBlood(2);
                if (IsEffect) 
                    AudioEngine::play2d("Audio/fx_health_potion.mp3");
                treasureType = 0;
            }
            else if (treasureType == 2)
            {
                treasureItem->getSprite()->setVisible(false);
                hero->setMaxShield(hero->getMaxShield() + 2);
                treasureItem->setInformationUnvisible();
                if (IsEffect)
                    AudioEngine::play2d("Audio/fx_health_potion.mp3");
                treasureType = 0;
            }
            else
            {
                int ex_Type = 0;
                switch (hero->getWeapon()->getType())
                {
                case 0:
                    treasureItem->getSprite()->setVisible(false);
                    treasureWeapon = Sprite::create("item/weapons.png");
                    treasureWeapon->setPosition(Vec2(600, 400));
                    treasureItem->changeSprite(treasureWeapon);
                    this->addChild(treasureWeapon, 4);
                    
                    ex_Type = 5;
                    /*auto exchangeWeapon = Gun::create();
                    hero->bindWeapon(exchangeWeapon);*/
                    break;
                case 1:
                    treasureItem->getSprite()->setVisible(false);
                    treasureWeapon = Sprite::create("item/quickGun.png");
                    treasureWeapon->setPosition(Vec2(600, 400));
                    treasureItem->changeSprite(treasureWeapon);
                    this->addChild(treasureWeapon, 6);
                    
                    ex_Type = 6;
                    break;
                case 2:
                    treasureItem->getSprite()->setVisible(false);
                    treasureWeapon = Sprite::create("item/Sword.png");
                    treasureWeapon->setPosition(Vec2(600, 400));
                    treasureItem->changeSprite(treasureWeapon);
                    this->addChild(treasureWeapon, 4);
                    
                    ex_Type = 3;
                    break;
                case 3:
                    treasureItem->getSprite()->setVisible(false);
                    treasureWeapon = Sprite::create("item/spear.png");
                    treasureWeapon->setPosition(Vec2(600, 400));
                    treasureItem->changeSprite(treasureWeapon);
                    this->addChild(treasureWeapon, 4);

                    ex_Type = 4;
                    break;
                default:
                    break;
                }
                if (treasureType == 5)
                {
                    auto gun = Gun::create();
                    hero->addChild(gun, 5);
                    hero->shiftWeapon(gun);

                }
                else if (treasureType == 6)
                {
                    auto gun = QuickGun::create();
                    hero->addChild(gun, 5);
                    hero->shiftWeapon(gun);
                }
                else if (treasureType == 3)
                {
                    auto sword = Sword::create();
                    hero->addChild(sword, 5);
                    hero->shiftWeapon(sword);
                }
                else if (treasureType == 4)
                {
                    auto spear = Spear::create();
                    hero->addChild(spear, 5);
                    hero->shiftWeapon(spear);
                }
                /*switch (treasureType)
                {
                case 3:
                    auto exchangeWeapon1 = Sword::create();
                    hero->shiftWeapon(exchangeWeapon1);
                    hero->addChild(exchangeWeapon1, 4);
                    break;
                case 4:
                    auto exchangeWeapon2 = Sword::create();
                    hero->shiftWeapon(exchangeWeapon2);
                    hero->addChild(exchangeWeapon2, 4);
                    break;
                case 5:
                    auto exchangeWeapon3 = Gun::create();
                    hero->shiftWeapon(exchangeWeapon3);
                    hero->addChild(exchangeWeapon3, 4);
                    break;
                case 6:
                    auto exchangeWeapon4 = QuickGun::create();
                    hero->shiftWeapon(exchangeWeapon4);
                    hero->addChild(exchangeWeapon4, 4);
                    break;
                default:
                    break;
                }*/
                if (IsEffect)
                    AudioEngine::play2d("Audio/fx_switch.mp3");
                treasureType = ex_Type;
            }
        }
        
    }
}

Vec2 RoomMap::getMonsterPosition()
{
    int minDistance = 10000;
    int distance = 0;
    int record = -1;
    for (INT32 j = 0; j < m_vMonster.size(); j++)
    {
        if (m_vMonster.at(j)->checkalive() && m_vMonster.at(j) != nullptr)
            if (!hero->getis_turn() && (m_vMonster.at(j)->getposition().x >= hero->getposition().x))
            {
                distance = sqrt((hero->getposition().x - m_vMonster.at(j)->getPosition().x) * (hero->getposition().x - m_vMonster.at(j)->getPosition().x) +
                    (hero->getposition().y - m_vMonster.at(j)->getPosition().y) * (hero->getposition().y - m_vMonster.at(j)->getPosition().y));
                if (distance < minDistance)
                {
                    minDistance = distance;
                    record = j;
                }
            }
            else if (hero->getis_turn() && (m_vMonster.at(j)->getposition().x <= hero->getposition().x))
            {
                distance = sqrt((hero->getposition().x - m_vMonster.at(j)->getPosition().x) * (hero->getposition().x - m_vMonster.at(j)->getPosition().x) +
                    (hero->getposition().y - m_vMonster.at(j)->getPosition().y) * (hero->getposition().y - m_vMonster.at(j)->getPosition().y));
                if (distance < minDistance)
                {
                    minDistance = distance;
                    record = j;
                }
            }
    }
    if (record != -1)
        return m_vMonster.at(record)->getposition()+ m_vMonster.at(record)->getPosition();
    else
        if (hero->getis_turn())
            return Vec2(1, 0.1);
        else
            return Vec2(-1, 0.1);
}

void RoomMap::createMonster()
{
    int randMonster=random(1,3);
    if (randMonster == 1)
    {
        auto monster1 = Monster::create();
        this->addChild(monster1, 4);
        monster1->createsnow(Vec2(400, 200));
        monster1->RestAction();
        monster1->bindhero(hero);
        monster1->scheduleUpdate();
        m_vMonster.pushBack(monster1);
    }
    else if (randMonster == 2)
    {
        auto monster1 = Pig::create();
        this->addChild(monster1, 4);
        monster1->createPig(Vec2(400, 200));
        monster1->RestAction();
        monster1->bindhero(hero);
        monster1->scheduleUpdate();
        m_vMonster.pushBack(monster1);
    }
    else
    {
        auto monster1 = CrawShoot::create();
        this->addChild(monster1, 4);
        monster1->creatCraw(Vec2(400, 200));
        monster1->RestAction();
        monster1->bindhero(hero);
        monster1->scheduleUpdate();
        m_vMonster.pushBack(monster1);
    }
    randMonster = random(1, 3);
    if (randMonster == 1)
    {
        auto monster2 = Monster::create();
        this->addChild(monster2, 4);
        monster2->createsnow(Vec2(400, 500));
        monster2->RestAction();
        monster2->bindhero(hero);
        monster2->scheduleUpdate();
        m_vMonster.pushBack(monster2);
    }
    else if (randMonster == 2)
    {
        auto monster2 = Pig::create();
        this->addChild(monster2, 4);
        monster2->createPig(Vec2(400, 500));
        monster2->RestAction();
        monster2->bindhero(hero);
        monster2->scheduleUpdate();
        m_vMonster.pushBack(monster2);
    }
    else
    {
        auto monster2 = CrawShoot::create();
        this->addChild(monster2, 4);
        monster2->creatCraw(Vec2(400, 500));
        monster2->RestAction();
        monster2->bindhero(hero);
        monster2->scheduleUpdate();
        m_vMonster.pushBack(monster2);
    }
    randMonster = random(1, 3);
    if (randMonster == 1)
    {
        auto monster3 = Monster::create();
        this->addChild(monster3, 4);
        monster3->createsnow(Vec2(1000, 100));
        monster3->RestAction();
        monster3->bindhero(hero);
        monster3->scheduleUpdate();
        m_vMonster.pushBack(monster3);
    }
    else if (randMonster == 2)
    {
        auto monster3 = Pig::create();
        this->addChild(monster3, 4);
        monster3->createPig(Vec2(1000, 100));
        monster3->RestAction();
        monster3->bindhero(hero);
        monster3->scheduleUpdate();
        m_vMonster.pushBack(monster3);
    }
    else if (randMonster == 3)
    {
        auto monster3 = CrawShoot::create();
        this->addChild(monster3, 4);
        monster3->creatCraw(Vec2(1000, 100));
        monster3->RestAction();
        monster3->bindhero(hero);
        monster3->scheduleUpdate();
        m_vMonster.pushBack(monster3);
    }
    randMonster = random(1, 3);
    if (randMonster == 1)
    {
        auto monster4 = Monster::create();
        this->addChild(monster4, 4);
        monster4->createsnow(Vec2(1000, 500));
        monster4->RestAction();
        monster4->bindhero(hero);
        monster4->scheduleUpdate();
        m_vMonster.pushBack(monster4);
    }
    else if (randMonster == 2)
    {
        auto monster4 = Pig::create();
        this->addChild(monster4, 4);
        monster4->createPig(Vec2(1000, 500));
        monster4->RestAction();
        monster4->bindhero(hero);
        monster4->scheduleUpdate();
        m_vMonster.pushBack(monster4);
    }
    else if (randMonster == 3)
    {
        auto monster4 = CrawShoot::create();
        this->addChild(monster4, 4);
        monster4->creatCraw(Vec2(1000, 500));
        monster4->RestAction();
        monster4->bindhero(hero);
        monster4->scheduleUpdate();
        m_vMonster.pushBack(monster4);
    }
    if (mnum - 1 == 6)
    {
        auto monster5 = Boss::create();
        this->addChild(monster5, 4);
        monster5->creatBoss(Vec2(650, 370));
        //monster5->RestAction();
        monster5->bindhero(hero);
        monster5->scheduleUpdate();
        m_vMonster.pushBack(monster5);
    }
}

void RoomMap::checkBullet()
{
    if (hero->getWeapon()->getType() != 2&&hero->getWeapon()->getType() != 3)
    {
        auto actionRemove = RemoveSelf::create();
        for (INT32 j = 0; j < m_vBullet.size(); j++)
        {

            if (abs((m_vBullet.at(j))->getPosition().x) > 3000 && abs((m_vBullet.at(j))->getPosition().y) > 3000) {
                (m_vBullet.at(j))->getSprite()->runAction(actionRemove);
                (m_vBullet.at(j))->removeFromParentAndCleanup(true);
                m_vBullet.eraseObject(m_vBullet.at(j));
                continue;
            }
            for (INT32 i = 0; i < m_vMonster.size(); i++)
            {
                //log("mon at: %f,%f", monster->getposition().x,monster->getposition().y);
                if (m_vMonster.at(i)->checkalive() && m_vMonster.at(i) != nullptr && m_vBullet.at(j) != nullptr)
                {
                    auto monsterRect = m_vMonster.at(i)->getSprite()->getBoundingBox();
                    auto bulletRect = (m_vBullet.at(j))->getSprite()->getBoundingBox();
                    /*auto p = (*iter)->getSprite()->getPosition();
                    auto rect = monster->getBoundingBox();*/

                    if (bulletRect.intersectsRect(monsterRect))
                    {
                        auto actionRemove = RemoveSelf::create();

                        log("yes");
                        m_vMonster.at(i)->beingAttack();


                        (m_vBullet.at(j))->getSprite()->runAction(actionRemove);
                        (m_vBullet.at(j))->removeFromParentAndCleanup(true);
                        m_vBullet.eraseObject(m_vBullet.at(j));
                        if (!m_vMonster.at(i)->checkalive())
                        {
                            //m_vMonster.at(i)->getSprite()->runAction(actionRemove);
                            m_vMonster.at(i)->removeAllChildrenWithCleanup(true);
                            m_vMonster.eraseObject(m_vMonster.at(i));
                        }
                        break;
                    }
                }
            }
        }
    }
}
TMXTiledMap* RoomMap::createmap(int num)
{
    if (num == 1)return TMXTiledMap::create("map/MonsterRoom1.tmx");
    if (num == 2)return TMXTiledMap::create("map/MonsterRoom2.tmx");
    if (num == 3)return TMXTiledMap::create("map/BirthRoom.tmx");
    if (num == 4)return TMXTiledMap::create("map/MonsterRoom2.tmx");
    if (num == 5)return TMXTiledMap::create("map/MonsterRoom1.tmx");
    if (num == 6)return TMXTiledMap::create("map/BossRoom.tmx");
    else return TMXTiledMap::create("map/BossRoom.tmx");
    /*else
    {
        Director::getInstance()->replaceScene(TableRoom::create());
    }*/

}
void RoomMap::transScene()
{

    for (int i = 0; i < 5; i++)
    {

        if (vecDoorOpen.at(i)->getBoundingBox().intersectsRect(hero->getBox()))
        {

            auto scene = RoomMap::createRoomScene(hero, mnum);
            Director::getInstance()->replaceScene(scene);
        }
    }
}
void RoomMap::generateDoor()
{
    for (int i = 1; i <= 5; i++)
    {
        Sprite* tmpSprite = Sprite::create("map/doorClose.png");
        tmpSprite->setPosition(Vec2(520 + i * 33, 690));
        this->addChild(tmpSprite, 3);
        vecDoorClose.pushBack(tmpSprite);
    }
}
void RoomMap::openDoor()
{
    for (int i = 0; i <= 4; i++)
    {
        vecDoorClose.at(i)->setVisible(false);
    }
    for (int i = 1; i <= 5; i++)
    {
        Sprite* tmpSprite = Sprite::create("map/doorOpen.png");
        tmpSprite->setPosition(Vec2(520 + i * 33, 680));
        this->addChild(tmpSprite, 3);
        vecDoorOpen.pushBack(tmpSprite);
    }
}

void RoomMap::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    is_attack = 0;
    if (keyCode == EventKeyboard::KeyCode::KEY_J && hero->getWeapon()->getType() == 1)
    {
        auto pBullet = hero->getWeapon()->createBullet();
        m_vBullet.pushBack(pBullet);
        this->addChild(pBullet, 10);
        //if (pig->checkalive() && pig != nullptr)
        pBullet->attack(hero->getposition(), hero->getis_turn(), getMonsterPosition());
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_L)
    {
        //keypressed_pick = false;
    }
}

