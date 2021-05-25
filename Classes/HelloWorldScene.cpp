/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Scene/GameStartScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{

    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "interface/ui_close.png",
                                           "interface/ui_close_pressed.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'interface/ui_close.png' and 'interface/ui_close_pressed.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + visibleSize.height -closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Press Any Key ", "Font/LockClock.ttf", 30);
    if (label == nullptr)
    {
        problemLoading("'Font/LockClock.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - 600));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("interface/start.png");
    if (sprite == nullptr)
    {
        problemLoading("'interface/start.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
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

    auto eventListener = EventListenerKeyboard::create();
    // 定义键盘按下处理函数
    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event) {
        log("key press %d key", keycode);
        Director::getInstance()->replaceScene(TitleScene::create());
    };
    /*eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode) {
            // 按下向左箭头，或A键
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            // 将与事件绑定的精灵向左移，按一下，移一下
            event->getCurrentTarget()->setPosition(--loc.x, loc.y);
            break;
            // 按下向右箭头，或D键
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            // 将与事件绑定的精灵向右移，按一下，移一下
            event->getCurrentTarget()->setPosition(++loc.x, loc.y);
            break;
            // 按下向上箭头，或W键
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            // 将与事件绑定的精灵向上移，按一下，移一下
            event->getCurrentTarget()->setPosition(loc.x, ++loc.y);
            break;
            // 按下向下箭头，或S键
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            // 将与事件绑定的精灵向下移，按一下，移一下
            event->getCurrentTarget()->setPosition(loc.x, --loc.y);
            break;

        }
    };*/
    // 将事件监听器与精灵进行绑定
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    SpriteFrame* frame = NULL;

    Vector<SpriteFrame*> array;
    std::ostringstream osr;

    for (int i = 1; i <= 4; ++i) {
        osr << "knight_move" << i << ".png";
        frame = SpriteFrame::create(osr.str(), Rect(0,0,64 ,60));
        if (frame == nullptr)
        {
            log("Actor/knight_move%d.png lost", i);
        }
        else
        {
            frame->setAnchorPoint(Vec2(0.5f, 0.f));
            array.pushBack(frame);
        }
        //frame = SpriteFrame::create(osr.str(), Rect(0, 0, 30, 30));

        osr.str("");
    }
    auto animation = Animation::createWithSpriteFrames(array, 0.1f);
    auto animate = Animate::create(animation);
    animation->setDelayPerUnit(0.2f);
    auto sprite10 = Sprite::create("Actor/knight_move1.png");
    sprite10->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(sprite10, 2);
    sprite10->runAction(RepeatForever::create(animate));
    /*auto sprite10 = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("Actor/knight_move1.png"));
    sprite10->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(sprite10, 3);
    sprite10->runAction(RepeatForever::create(animate));*/
    return true;

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
