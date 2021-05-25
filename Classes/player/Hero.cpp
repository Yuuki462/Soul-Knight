#include "Hero.h"

USING_NS_CC;
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
Animate* CallAction(bool rest_move)//0为rest，1为move
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrame* frame = NULL;

    Vector<SpriteFrame*> array;
    std::ostringstream osr;
    if (rest_move == 0)
    {
        for (int i = 1; i <= 4; ++i) {
            osr << "Actor/knight_rest" << i << ".png";
            frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
            if (frame == nullptr)
            {
                log("Actor/knight_rest%d.png lost", i);
            }
            else
            {
                frame->setAnchorPoint(Vec2(0.5f, 0.f));
                array.pushBack(frame);
            }

            osr.str("");
        }
    }
    else
    {
        for (int i = 1; i <= 4; ++i) {
            osr << "Actor/knight_move" << i << ".png";
            frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
            if (frame == nullptr)
            {
                log("Actor/knight_move%d.png lost", i);
            }
            else
            {
                frame->setAnchorPoint(Vec2(0.5f, 0.f));
                array.pushBack(frame);
            }
            osr.str("");
        }
    }
    auto animation = Animation::createWithSpriteFrames(array,0.1f);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.2f);
    auto animate = Animate::create(animation);
    animate->retain();
    return animate;

}
Animate* Attack(bool left_right)//0为朝左，1为朝右
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<SpriteFrame*>m_rightActionVec;
    Vector<SpriteFrame*>m_leftActionVec;
    int actionStep = 4;
    SpriteFrame* frame_r = nullptr;
    SpriteFrame* frame_l = nullptr;
    for (int i = 1; i <= actionStep+1; i++)
    {
        frame_r = SpriteFrame::create(StringUtils::format("item/bullets/sword_action%d.png", i%4),
            Rect(0, 0, 60, 60));
        frame_l = SpriteFrame::create(StringUtils::format("item/bullets/sword_action%d.png", i%4),
            Rect(0, 0, 60, 60));
        if (frame_l == nullptr || frame_r == nullptr)
        {
            log("animate sword_action%d.png lost", i);
        }
        else
        {
            frame_r->setAnchorPoint(Vec2(0.f, 0.5f));
            m_rightActionVec.pushBack(frame_r);
            frame_l->setAnchorPoint(Vec2(1.f, 0.5f));
            m_leftActionVec.pushBack(frame_l);
        }
    }
    /*frame_r = SpriteFrame::create(StringUtils::format("item/sword.png"), Rect(0, 0, 60, 60));
    m_rightActionVec.pushBack(frame_r);
    m_leftActionVec.pushBack(frame_r);*/
    if (left_right == 1)
    {
        auto animation = Animation::createWithSpriteFrames(m_rightActionVec, 0.1f);
        auto animate = Animate::create(animation);
        animation->setDelayPerUnit(0.2f);
        return animate;
    }
    else
    {
        auto animation = Animation::createWithSpriteFrames(m_leftActionVec, 0.1f);
        auto animate = Animate::create(animation);
        animation->setDelayPerUnit(0.2f);
        return animate;
    }
;
    
}

void Hero::bindsprite(Sprite* sprite)
{
    mysprite = sprite;
}
void Hero::bindsword(Sprite*sword)
{
    m_Sword = sword;
}
void Hero::RestAction()
{
    mysprite->stopAllActions();
    mysprite->runAction(CallAction(0));
}
void Hero::MoveAction()
{
    mysprite->stopAllActions();
    mysprite->runAction(CallAction(1));
}
void Hero::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
        keypressed[2] = true;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
        keypressed[3] = true;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_W:
        keypressed[0] = true;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case EventKeyboard::KeyCode::KEY_S:
        keypressed[1] = true;
        break;
    case EventKeyboard::KeyCode::KEY_J:
        if(c_facing==right)
            m_Sword->runAction(Attack(1));
        else
            m_Sword->runAction(Attack(0));
        break;
    }
}
void Hero::onKeyreleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
        keypressed[2] = false;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
        keypressed[3] = false;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_W:
        keypressed[0] = false;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
    case EventKeyboard::KeyCode::KEY_S:
        keypressed[1] = false;
        break;
    }
}
void Hero::update(float delta)
{
    
    auto position = mysprite->getPosition();
    if (keypressed[0] == true)
    {
        position.y += m_speed;
    }
    if (keypressed[1] == true)
    {
        position.y -= m_speed;
    }
    if (keypressed[2] == true)
    {
        position.x -= m_speed;
    }
    if (keypressed[3] == true)
    {
        position.x += m_speed;
    }
    if (position != mysprite->getPosition() && being_move == false)
    {
        MoveAction();
        being_move = true;
    }
    else if (position == mysprite->getPosition() && being_move == true)
    {
        RestAction();
        being_move = false;
    }
    if (position.x > mysprite->getPosition().x && c_facing == left)
    {
        
        m_Sword->setFlippedX(false);
        mysprite->setFlippedX(false);
        c_facing = right;
    }
    else if (position.x < mysprite->getPosition().x && c_facing == right)
    {
        
        m_Sword->setFlippedX(true);
        mysprite->setFlippedX(true);
        c_facing = left;
    }
    if (c_facing == left)
        m_Sword->setPosition(position.x - 10, position.y + 15);
    else
        m_Sword->setPosition(position.x + 10, position.y + 15);
    mysprite->setPosition(position);
}
int Hero::getBlood_v() 
{
    return blood_v;
}
int Hero::getShield()
{
    return shield;
}
void Hero::setSpeed(int c_speed)
{
    m_speed = c_speed;
}