#include "GameStartScene.h"
#include "TableRoom.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;
Scene* TitleScene::createScene()
{
    return TitleScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool TitleScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto startMenu = MenuItemImage::create(
        "startNormal.png",
        "startSelected.png",
        CC_CALLBACK_1(TitleScene::menuStartCallback, this));
    if (startMenu == nullptr ||
        startMenu->getContentSize().width <= 0 ||
        startMenu->getContentSize().height <= 0)
    {
        problemLoading("'startNormal.png' and 'startSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2 - startMenu->getContentSize().width / 2;
        float y = origin.y + startMenu->getContentSize().height / 2 + 90.0;
        startMenu->setScaleX(1.5f);
        startMenu->setPosition(Vec2(x, y));
    }
    auto endMenu = MenuItemImage::create(
        "interface/ui_close.png",
        "interface/ui_close_pressed.png",
        CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
    if (endMenu == nullptr ||
        endMenu->getContentSize().width <= 0 ||
        endMenu->getContentSize().height <= 0)
    {
        problemLoading("'endNormal.png' and 'endSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - endMenu->getContentSize().width / 2;
        float y = origin.y + visibleSize.height - endMenu->getContentSize().height / 2;
        endMenu->setPosition(Vec2(x, y));
    }

    auto menu = Menu::create(startMenu, endMenu, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto startLabel = Label::createWithTTF("Start Game", "Font/pixel_bold.ttf", 28);
    if (startLabel == nullptr)
    {
        problemLoading("'Font/pixel_bold.ttf'");
    }
    else
    {
        startLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 110.0,
            origin.y + startLabel->getContentSize().height / 2 + 140.0));
        this->addChild(startLabel, 1);
    }

    auto sprite2 = Sprite::create("interface/start_2.png");
    auto sprite3 = Sprite::create("interface/start.png");
    if (sprite2 == nullptr|| sprite3==nullptr)
    {
        problemLoading("'interface/start_2.png'&¡®interface/start.png¡¯");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x+290, visibleSize.height / 2 + origin.y+50));

        // add the sprite as a child to this layer
        this->addChild(sprite3, 0);
        this->addChild(sprite2, 0);
    }
    auto gameName = Sprite::create("interface/title_zh.png");
    if (gameName == nullptr ||
        gameName->getContentSize().width <= 0 ||
        gameName->getContentSize().height <= 0)
    {
        problemLoading("'interface/title_zh.png'");
    }
    else
    {
        gameName->setPosition(Vec2(origin.x + gameName->getContentSize().width / 2 + 50,
            visibleSize.height + origin.y - gameName->getContentSize().height));
        this->addChild(gameName, 0);
    }
    return true;
}
void TitleScene::menuStartCallback(Ref* pSender) {
    auto scene = TableRoom::create();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    Director::getInstance()->replaceScene(scene);
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}