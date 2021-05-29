#include"TableRoom.h"
#include "player/Hero.h"

USING_NS_CC;

Scene* TableRoom::createScene()
{
    auto scene = Scene::create();
    //auto layer = TableRoom::create();
    //scene->addChild(layer);
    //scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    return scene;
    /*auto scene = Scene::createWithPhysics();
    auto layer = TableRoom::create();
    scene->addChild(layer);
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    return scene;*/
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
    //Sprite* edgeSpace = Sprite::create("interface/hire_room_0.png");
    if (floor == nullptr)
    {
        problemLoading("'hire_room_0.png'");
    }
    else
    {
        // position the sprite on the center of the screen

        /*PhysicsBody* boundBody = PhysicsBody::createEdgeBox(edgeSpace->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
        boundBody->getShape(0)->setFriction(0.0f);
        boundBody->getShape(0)->setRestitution(1.0f);

        edgeSpace->setPhysicsBody(boundBody);
        edgeSpace->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(edgeSpace);
        edgeSpace->setTag(0);*/



        //PhysicsBody* edge = PhysicsBody::createEdgeBox(floor->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
        //edge->setGravityEnable(false);

        //edge->setCategoryBitmask(0x1); // 0001
        //edge->setContactTestBitmask(0x0); // 0100
        //edge->setCollisionBitmask(0x3c); // 0011
        //floor->setPhysicsBody(edge);
        floor->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(floor, 1, 0x1);
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
    
    /*auto Sword = Sprite::create("item/sword.png");
    Sword->setPosition(Vec2(visibleSize.width / 2 + origin.x+90, visibleSize.height / 2 + origin.y+20));
    addChild(Sword, 5);*/
    
    /*gun->getSprite()->setPosition(Vec2(visibleSize.width / 2 + origin.x + 90, visibleSize.height / 2 + origin.y + 20));
    addChild(gun->getSprite(), 5);*/
    
    Hero*hero=Hero::create();
    hero->getSprite()->setPosition(Vec2(visibleSize.width / 2 + origin.x + 75,
        visibleSize.height / 2 + origin.y));
    this->addChild(hero, 4);
    
    
    /*hero->bindWeapon(gun);*/
    /*hero->bindsword(Sword);*/
    hero->RestAction();
    auto keyBoardListenerHero = EventListenerKeyboard::create();
    keyBoardListenerHero->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, hero);
    keyBoardListenerHero->onKeyReleased = CC_CALLBACK_2(Hero::onKeyreleased, hero);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListenerHero, this);
    
    BulletLayer* bulletLayer = BulletLayer::create();
    bulletLayer->retain();
    bulletLayer->bindHero(hero);
    this->addChild(bulletLayer, 10);

    hero->scheduleUpdate();
    
    return true;
}

