

#include"TableRoom.h"
#include "player\Hero.h"
#include "Weapon/Sword.h"
USING_NS_CC;

Scene* TableRoom::createScene()
{
    Scene* scene = Scene::create();
    TableRoom* layer = TableRoom::create();
    scene->addChild(layer);
    return scene;
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool TableRoom::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto floor = Sprite::create("interface/hire_room_0.png");
    if (floor == nullptr)
    {
        problemLoading("'floor.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        floor->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(floor, 0);
    }

    auto table = Sprite::create("table.png");
    if (table == nullptr)
    {
        problemLoading("'table.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        table->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(table, 2);
    }

    auto carpet = Sprite::create("carpet.png");
    if (carpet == nullptr)
    {
        problemLoading("'carpet.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        carpet->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(carpet, 1);
    }

    auto sofa = Sprite::create("sofa.png");
    if (sofa == nullptr)
    {
        log("sofa.png not found");
    }
    else
    {
        sofa->setPosition(Vec2(visibleSize.width / 2 + origin.x - 100.0,
            visibleSize.height / 2 + origin.y + 150.0));
        addChild(sofa, 2);
    }

    auto leftChair = Sprite::create("chair1.png");
    if (leftChair == nullptr)
    {
        log("chair1.png not found");
    }
    else
    {
        leftChair->setPosition(Vec2(visibleSize.width / 2 + origin.x - 70.0,
            visibleSize.height / 2 + origin.y));
        addChild(leftChair, 3, 102);
    }

    auto rightChair = Sprite::create("chair2.png");
    if (rightChair == nullptr)
    {
        log("chair2.png not found");
    }
    else
    {
        rightChair->setPosition(Vec2(visibleSize.width / 2 + origin.x + 70.0,
            visibleSize.height / 2 + origin.y));
        addChild(rightChair, 3, 101);
    }

    auto fridge = Sprite::create("fridge.png");
    if (fridge == nullptr)
    {
        log("fridge.png not found");
    }
    else
    {
        fridge->setPosition(Vec2(visibleSize.width / 2 + origin.x - 270.0,
            visibleSize.height / 2 + origin.y + 160.0));
        addChild(fridge, 3, 103);
    }

    auto board = Sprite::create("board.png");
    if (board == nullptr)
    {
        log("board.png not found");
    }
    else
    {
        board->setPosition(Vec2(visibleSize.width / 2 + origin.x + 170.0,
            visibleSize.height / 2 + origin.y + 270.0));
        addChild(board, 3, 104);
    }

    auto labTable = Sprite::create("labTable.png");
    if (labTable == nullptr)
    {
        log("labTable.png not found");
    }
    else
    {
        labTable->setPosition(Vec2(visibleSize.width / 2 + origin.x + 280.0,
            visibleSize.height / 2 + origin.y + 50.0));
        addChild(labTable, 3, 106);
    }

    auto television = Sprite::create("TV.png");
    if (television == nullptr)
    {
        log("TV.png not found");
    }
    else
    {
        television->setPosition(Vec2(visibleSize.width / 2 + origin.x + 300.0,
            visibleSize.height / 2 + origin.y - 240.0));
        addChild(television, 3, 105);
    }

    auto part = Sprite::create("part.png");
    if (part == nullptr)
    {
        log("part.png not found");
    }
    else
    {
        part->setPosition(Vec2(visibleSize.width / 2 + origin.x + 300.0,
            visibleSize.height / 2 + origin.y - 150.0));
        addChild(part, 3, 107);
    }

    auto can = Sprite::create("can.png");
    if (can == nullptr)
    {
        log("can.png not found");
    }
    else
    {
        can->setPosition(Vec2(visibleSize.width / 2 + origin.x - 320.0,
            visibleSize.height / 2 + origin.y - 230.0));
        addChild(can, 3, 108);
    }

    auto machine = Sprite::create("machine.png");
    if (machine == nullptr)
    {
        log("machine.png not found");
    }
    else
    {
        machine->setPosition(Vec2(visibleSize.width / 2 + origin.x - 320.0,
            visibleSize.height / 2 + origin.y + 10.0));
        addChild(machine, 3, 109);
    }

    auto plant = Sprite::create("plant.png");
    if (plant == nullptr)
    {
        log("plant.png not found");
    }
    else
    {
        plant->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150.0,
            visibleSize.height / 2 + origin.y + 170.0));
        addChild(plant, 3, 110);
    }

    auto box = Sprite::create("box.png");
    if (box == nullptr)
    {
        log("box.png not found");
    }
    else
    {
        box->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200.0,
            visibleSize.height / 2 + origin.y + 130.0));
        addChild(box, 3, 111);
    }

    auto eggTwist = Sprite::create("eggTwist.png");
    if (eggTwist == nullptr)
    {
        log("eggTwist.png not found");
    }
    else
    {
        eggTwist->setPosition(Vec2(visibleSize.width / 2 + origin.x - 220.0,
            visibleSize.height / 2 + origin.y + 160.0));
        addChild(eggTwist, 3, 112);
    }


    auto canBed = Sprite::create("canBed.png");
    if (canBed == nullptr)
    {
        log("canBed.png not found");
    }
    else
    {
        canBed->setPosition(Vec2(visibleSize.width / 2 + origin.x - 200.0,
            visibleSize.height / 2 + origin.y - 230.0));
        addChild(canBed, 3, 113);
    }


    auto sprite = Sprite::create("Actor/knight_rest1.png");
    if (sprite == nullptr)
    {
        log("sprite.png not found");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x + 75,
            visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 4);
    }

    auto sprite1 = Sprite::create("item/sword.png");
    if (sprite1 == nullptr)
    {
        log("sprite1.png not found");
    }
    else
    {
        sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 75,
            visibleSize.height / 2 + origin.y + 5));
        this->addChild(sprite1, 4);
    }



    hero = Hero::create();
    this->addChild(hero, 4);
    Sword* sword = Sword::create();
    this->addChild(sword, 4);
    hero->bindsprite(sprite);
    sword->bindsprite(sprite1);
    hero->setmymainweapon(sword);
    hero->RestAction();
    auto keyBoardListenerHero = EventListenerKeyboard::create();
    keyBoardListenerHero->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
    keyBoardListenerHero->onKeyReleased = CC_CALLBACK_2(Hero::onKeyreleased, hero);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListenerHero, this);
    hero->scheduleUpdate();
    sword->scheduleUpdate();
    m_pMap = TMXTiledMap::create("map/SafeMap.tmx");

    addChild(m_pMap, 3);
    this->scheduleUpdate();


    return true;
}

void TableRoom::isCollision()
{
    Vec2 pos = hero->getposition();

    barrier = m_pMap->getObjectGroup("barrier");
    ValueVector object = barrier->getObjects();
    for (ValueVector::iterator it = object.begin(); it != object.end(); it++) 
    {
        Value obj = *it;
        ValueMap map = obj.asValueMap();
        int x = map.at("x").asInt();
        int y = map.at("y").asInt();
        int width = map.at("width").asInt();
        int height = map.at("height").asInt();
        if (pos.x<x && pos.x>x - 10)
        {
            if(1)//陳衵
                hero->setSpeed(0);
            else
                hero->setSpeed(3);
        }
        else if (pos.x > x+width && pos.x < x+width + 10)
        {
            if (1)//陳酘
                hero->setSpeed(0);
            else
                hero->setSpeed(3);
        }
        else if (pos.y >y && pos.y< y+ 10)
        {
            if (1)//陳狟
                hero->setSpeed(0);
            else
                hero->setSpeed(3);
        }
        else if(pos.y < y-height && pos.y > y-height - 10)
        {
            if (1)//陳奻
                hero->setSpeed(0);
            else
                hero->setSpeed(3);
        }
        /*if (pos.x > (map.at("x").asInt()) && pos.x < (map.at("x").asInt() + map.at("width").asInt()) &&
            pos.y <(map.at("y").asInt()) && pos.y > (map.at("y").asInt() - map.at("height").asInt()))
        {

            hero->setSpeed(0);
        }
        else
        {
            hero->setSpeed(3);
        }*/
    }
  

}
void TableRoom::update(float delta)
{


     isCollision();
        
    //startgame();
}
/*
void TableRoom::startgame()
{
    if (transfer->getBoundingBox().containsPoint(hero->getposition()))
        Director::getInstance()->end();
}*/
