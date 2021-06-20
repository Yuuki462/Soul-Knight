#include "Monster.h"
#include "Scene\TableRoom.h"
USING_NS_CC;
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/*bool Monster::init()
{
    Sprite* pmonster = Sprite::create("Actor/Monster/snow_monster_stay1.png");
    if (pmonster == nullptr)
    {
        log("Actor/Monster/snow_monster_stay1.png not found");
    }
    else
    {
        int x = random(500, 1000);
        int y = random(100, 700);
        pmonster->setPosition(Vec2(x, y));
        this->addChild(pmonster, 4);
    }
    bindsprite(pmonster);
    return true;
}*/

void Monster::createsnow(Vec2 position)
{
    Sprite* pmonster = Sprite::create("Actor/Monster/snow_monster_stay1.png");
    if (pmonster == nullptr)
    {
        log("Actor/Monster/snow_monster_stay1.png not found");
    }
    else
    {
        pmonster->setPosition(position);
        this->getParent()->addChild(pmonster, 4);
    }
    bindsprite(pmonster);
}
Animate* CallMonsterAction(bool rest_move)//0为rest，1为move
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrame* frame = NULL;

    Vector<SpriteFrame*> array;
    std::ostringstream osr;
    if (rest_move == 0)
    {
        for (int i = 1; i <= 4; ++i) {
            osr << "Actor/Monster/snow_monster_stay" << i << ".png";
            frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
            if (frame == nullptr)
            {
                log("Actor/Monster/snow_monster_stay", i);
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
            osr << "Actor/Monster/snow_monster_move" << i << ".png";
            frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
            if (frame == nullptr)
            {
                log("Actor/Monster/snow_monster_move.png lost", i);
            }
            else
            {
                frame->setAnchorPoint(Vec2(0.5f, 0.f));
                array.pushBack(frame);
            }
            osr.str("");
        }
    }
    auto animation = Animation::createWithSpriteFrames(array, 0.1f);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.2f);
    auto animate = Animate::create(animation);
    animate->retain();
    return animate;

}
Animate* AttackShock()
{
    Vector<SpriteFrame*>shockVec;
    SpriteFrame* frame = nullptr;
    for (int i = 1; i <= 4; i++)
    {
        frame = SpriteFrame::create(StringUtils::format("item/bullets/shock_%d.png", i),
            Rect(0, 0, 60, 60));        
        if (frame == nullptr)
        {
            log("item/bullets/shock_%d.png", i);
        }
        else
        {
            frame->setAnchorPoint(Vec2(0.f, 0.5f));
            shockVec.pushBack(frame);
        }
        
    }
    frame = SpriteFrame::create(StringUtils::format("item/bullets/shock.png"),
        Rect(0, 0, 60, 60));
    frame->setAnchorPoint(Vec2(0.f, 0.5f));
    shockVec.pushBack(frame);
    auto animation = Animation::createWithSpriteFrames(shockVec, 0.1f);
    auto animate = Animate::create(animation);
    animation->setDelayPerUnit(0.2f);
    return animate;
}

void Monster::bindsprite(Sprite* sprite)
{
    mymonster = sprite;
}

void Monster::RestAction()
{
    state = 0;
    mymonster->stopAllActions();
    mymonster->runAction(CallMonsterAction(0));
}
void Monster::MoveAction()
{
    state = 1;
    mymonster->stopAllActions();
    mymonster->runAction(CallMonsterAction(1));
}
void Monster::bindhero(Hero* hero)
{
    m_hero = hero;
}
Vec2 Monster::getposition()
{
    return mymonster->getPosition();
}
void Monster::setfacing()
{

    if (m_hero->getposition().x > getposition().x&&c_facing==left)
    {
        mymonster->setFlippedX(false);
        c_facing = right;
    }
    else if(m_hero->getposition().x < getposition().x && c_facing == right)
    {
        mymonster->setFlippedX(true);
        c_facing = left;
    }
}
int Monster::getdistance()
{
    int distance = sqrt((m_hero->getposition().x - mymonster->getPosition().x) * (m_hero->getposition().x - mymonster->getPosition().x) +
        (m_hero->getposition().y - mymonster->getPosition().y) * (m_hero->getposition().y - mymonster->getPosition().y));
    return distance;
}
void Monster::wander()
{
    auto m_position = mymonster->getPosition();
    
    //防止快速抽搐
    if (controltime == 50)
        controltime = 0;
    if (controltime == 0)
    {
        setfacing();
        move_rest = random(0, 1);
        orien = random(1, 4);  
        if (move_rest == 0)
            RestAction();
        else
            MoveAction();
    }
    if(move_rest==1)
    {
        switch (orien) {
        case 1:
            if (banmove != 0)
                m_position.y += m_speed;
            break;
        case 2:
            if (banmove != 1)
                m_position.y -= m_speed;
            break;
        case 3:
            if (banmove != 2)
            {
                mymonster->setFlippedX(true);
                c_facing = left;
                m_position.x -= m_speed;
            }
            break;
        case 4:
            if (banmove != 3)
            {
                mymonster->setFlippedX(false);
                c_facing = right;
                m_position.x += m_speed;
            }
            break;
        }
        mymonster->setPosition(m_position);
    }
}
void Monster::track()
{
    setfacing();
    auto m_position = mymonster->getPosition();
    auto h_position = m_hero->getposition();
    if (m_position.x < h_position.x&&banmove!=3)
    {
        m_position.x += m_speed;
    }
    else if (m_position.x > h_position.x && banmove != 2)
    {
        m_position.x -= m_speed;
    }
    if (m_position.y < h_position.y && banmove != 0)
    {
        m_position.y += m_speed;
    }
    else if (m_position.y > h_position.y && banmove != 1)
    {
        m_position.y -= m_speed;
    }
    mymonster->setPosition(m_position);
}
void Monster::update(float delta)
{
    if (!be_Attack&&alive&&m_hero->checkalive()&&m_hero!=nullptr)
    {
        auto h_position = m_hero->getposition();
        if (attacttime < 300)
            attacttime++;
        if (attacttime == 300)
        {
            if (getdistance() > attackrange)
                track();
            else if (getdistance() <= attackrange)
            {
                is_attacking = 1;

                
                auto delay = DelayTime::create(3.f);
                auto checkoverFunc = CallFunc::create([&]() {
                    isover();
                    });
                auto seq = Sequence::create(jump(h_position), checkoverFunc, delay, nullptr);
                //mymonster->runAction(jump(h_position));
                mymonster->runAction(seq);
                attacttime = 0;
            }
        }
        else if (attacttime < 300 && !is_attacking)
        {
            controltime++;
            wander();
        }
        if (is_over == 1)
        {
            int RandAttact = random(100, 400);
            Sprite* shock = Sprite::create("item/bullets/shock.png");
            if (c_facing == left)
                shock->setPosition(Vec2(getposition().x - 10, getposition().y));
            else
                shock->setPosition(Vec2(getposition().x - 33, getposition().y));
            this->addChild(shock, 100000);
            //shock->runAction(AttackShock());
            shock->runAction(AttackShock());
            if (shock->getBoundingBox().intersectsRect(m_hero->getBox()))
                m_hero->beingAttack(1,damage);
            this->removeChildByTag(100000);
            is_over = 0;
            is_attacking = 0;
        }
        
    }
}
void Monster::isover()
{
    is_over = 1;
}
int Monster::getBlood_v()
{
    return blood_v;
}
JumpTo* Monster::jump(Vec2 h_position)
{
    auto dis = h_position;
    auto jumpaction = JumpTo::create(1.f, dis, 30.f, 1);
    return jumpaction;
}

void Monster::beingAttack()
{
    be_Attack = 1;
    auto checkoverFunc = CallFunc::create([&]() {
        AttackOver();
        });
    if (m_hero->getposition().x > getposition().x)
    {
        auto jumpaction = JumpTo::create(0.8f, Vec2(getposition().x - 5, getposition().y), 30.f, 1);
        auto seq = Sequence::create(jumpaction, checkoverFunc, nullptr);
        mymonster->runAction(seq);
    }
    else
    {
        auto jumpaction = JumpTo::create(0.8f, Vec2(getposition().x + 5, getposition().y), 30.f, 1);
        auto seq = Sequence::create(jumpaction, checkoverFunc, nullptr);
        mymonster->runAction(seq);
    }
    blood_v -= m_hero->MainWeapondamage();
    if (blood_v <= 0)
        die();
}

void Monster::die()
{
    alive = 0;
    this->stopAllActions();
    auto dieSprite = Sprite::create("Actor/Monster/snow_monster_dead.png");

    if (dieSprite == nullptr)
    {
        log("dead not available");
    }
    else
    {
        dieSprite->setPosition(mymonster->getPosition());
        this->getParent()->addChild(dieSprite, 5);
    }
    mymonster->setVisible(false);
}

void Monster::AttackOver()
{
    be_Attack = 0;
}

Rect Monster::getBox()
{
    return mymonster->getBoundingBox();
}

int Monster::checkalive()
{
    return alive;
}

void Monster::setbanmove(int ban)
{
    banmove = ban;
}


