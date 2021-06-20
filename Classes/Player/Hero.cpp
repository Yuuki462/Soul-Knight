#include "Hero.h"
#include "Scene/PauseMenu.h"
USING_NS_CC;

Hero* Hero::m_pPresentHero = nullptr;

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
Vec2 Hero::getposition()
{
    return mysprite->getPosition();
}
void Hero::bindsprite(Sprite* sprite)
{
    mysprite = sprite;
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
    case EventKeyboard::KeyCode::KEY_P:
        Director::getInstance()->pushScene(PauseMenu::create());
        break;
        /*
    case EventKeyboard::KeyCode::KEY_J:
        if(c_facing==left)
            m_pWeapon->attack(0);
        else
            m_pWeapon->attack(1);
            */
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
    if (alive)
    {
        healtime++;
        if (healtime > 150)
        {
            healShield();
            healtime = 0;
        }
        auto position = mysprite->getPosition();
        if (keypressed[0] == true)
        {
            if (banmove != 0)
                position.y += m_speed;
        }
        if (keypressed[1] == true)
        {
            if (banmove != 1)
                position.y -= m_speed;
        }
        if (keypressed[2] == true)
        {
            if (banmove != 2)
                position.x -= m_speed;
        }
        if (keypressed[3] == true)
        {
            if (banmove != 3)
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
            mysprite->setFlippedX(false);
            m_pWeapon->getSprite()->setFlippedX(false);
            is_turn = 0;
            c_facing = right;
        }
        else if (position.x < mysprite->getPosition().x && c_facing == right)
        {
            mysprite->setFlippedX(true);
            m_pWeapon->getSprite()->setFlippedX(true);
            is_turn = 1;
            c_facing = left;

        }
        if (c_facing == right)
            m_pWeapon->getSprite()->setPosition(position.x + 10, position.y + 15);
        else if (c_facing == left)
            m_pWeapon->getSprite()->setPosition(position.x - 10, position.y + 15);
        mysprite->setPosition(position);
    }

}

Rect Hero::getBox()
{
    return mysprite->getBoundingBox();
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
bool Hero::getis_turn()
{
    return is_turn;
}
void Hero::setWeapon(Weapon* pWeapon)
{
    bindWeapon(pWeapon);
    m_pWeapon->getSprite()->setPosition(mysprite->getPosition().x + 15, mysprite->getPosition().y + 20);
}

void Hero::bindWeapon(Weapon* weapon)
{
    m_pWeapon = weapon;
}

Weapon* Hero::getWeapon()
{
    return m_pWeapon;
}

Sprite* Hero::getSprite()
{
    return mysprite;
}

Hero* Hero::getInstance()
{
    return m_pPresentHero;
}

void Hero::addpicture()
{
    if (mysprite != nullptr)
    {
        mysprite->setPosition(Vec2(100, 100));
        this->addChild(mysprite);
    }
}

void Hero::setname(std::string str)
{
    name = str;
}
std::string Hero::getname()
{
    return name;
}
Rect Hero::getSwordBox()
{
    return m_pWeapon->getBox();
}

int Hero::MainWeapondamage()
{
    return m_pWeapon->getDamage();
}
void Hero::beingAttack(bool orient,int damage)
{
    healtime = 0;
    if (shield >= damage)
        shield -= damage;
    else
    {
        shield = 0;
        blood_v = blood_v - damage + shield;
    }
    if (orient == 0)
    {
        mysprite->setPosition(Vec2(getposition().x + 5, getposition().y));
        mysprite->setFlippedX(true);
        m_pWeapon->getSprite()->setFlippedX(true);
        is_turn = 1;
    }
    else
    {
        mysprite->setPosition(Vec2(getposition().x - 5, getposition().y));
        mysprite->setFlippedX(false);
        m_pWeapon->getSprite()->setFlippedX(false);
        is_turn = 0;
    }
    if (blood_v <= 0)
        die();
}

void Hero::die()
{
    alive = 0;
    this->stopAllActions();
    auto dieSprite = Sprite::create("Actor/knight_down.png");

    if (dieSprite == nullptr)
    {
        log("dead not available");
    }
    else
    {
        dieSprite->setPosition(mysprite->getPosition());
        this->getParent()->addChild(dieSprite, 5);
    }
    mysprite->setVisible(false);
    this->removeAllChildrenWithCleanup(true);
}
void Hero::createHero()
{
    Sprite* phero = Sprite::create("Actor/knight_rest1.png");
    if (phero == nullptr)
    {
        log("sprite10.png not found");
    }
    else
    {
        phero->setPosition(Vec2(600, 400));
        this->getParent()->addChild(phero, 4);
    }
    bindsprite(phero);
}
void Hero::setbanmove(int way)
{
    banmove = way;
}
void Hero::createHero(Vec2 position)
{
    Sprite* phero = Sprite::create("Actor/knight_rest1.png");
    if (phero == nullptr)
    {
        log("sprite10.png not found");
    }
    else
    {
        phero->setPosition(position);
        //this->getParent()->addChild(phero, 4);
        this->addChild(phero, 4);
    }
    bindsprite(phero);
}
void Hero::shiftWeapon(Weapon*_weapon)
{
    m_pWeapon->removeFromParentAndCleanup(true);
    setWeapon(_weapon);

}

void Hero::setBlood(int _blood)
{
    blood_v = _blood;
}

void Hero::setshield(int _shield)
{
    shield = _shield;
}

void Hero::setcoin(int _coin)
{
    m_coin = _coin;
}

int Hero::getSpeed()
{
    return m_speed;
}

int Hero::getcoin()
{
    return m_coin;
}

void Hero::healShield()
{
    if (shield != maxshield)
        shield++;
}

bool Hero::checkalive()
{
    return alive;
}

void Hero::recoverBlood(int _blood)
{
    if (blood_v + _blood > maxblood)
        blood_v = maxblood;
    else
        blood_v += _blood;
}

void Hero::setMaxShield(int _maxshield)
{
    maxshield = _maxshield;
}

int Hero::getMaxShield()
{
    return maxshield;
}