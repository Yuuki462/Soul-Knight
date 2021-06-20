#include"CloseMonster.h"
USING_NS_CC;


Animate* CallPigAction(bool rest_move)//0为rest，1为move
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrame* frame = NULL;

    Vector<SpriteFrame*> array;
    std::ostringstream osr;
    if (rest_move == 0)
    {
        
        array.pushBack(SpriteFrame::create("Actor/Monster/pig_monster1.png", Rect(0, 0, 64, 60)));
        array.pushBack(SpriteFrame::create("Actor/Monster/pig_monster2.png", Rect(0, 0, 64, 60)));

    }
    else
    {
        for (int i = 2; i <= 5; ++i) {
            osr << "Actor/Monster/pig_monster" << i << ".png";
            frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
            if (frame == nullptr)
            {
                log("Actor/Monster/pig_monster1.png", i);
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


void Pig::dash()
{
    MoveAction();
    is_over = 0;
    auto move = MoveBy::create(1.0f, Vec2(2*(m_hero->getposition() - getposition())));
    auto checkoverFunc = CallFunc::create([&]() {
        isover();
        });
    auto seq = Sequence::create(move, checkoverFunc, nullptr);
    
    mymonster->runAction(seq);
}


void Pig::update(float delta)
{
    if (!be_Attack&&alive && m_hero->checkalive() && m_hero != nullptr)
    {
        
        if (checktime < 100)
        {
            checktime++;
            if(!state)
            MoveAction();
            track();
        }
        else
        {

            attacttime++;
            if (getdistance() < attackrange)
            {
                
                if (attacttime > 100)
                {
                    dash();
                    attacttime = 0;
                }
            }
            if (is_over)
            {
                AttackOnce = 1;
                controltime++;
                wander();
            }
            
        }
        if (!is_over&&AttackOnce)
        {
            
            if (mymonster->getBoundingBox().intersectsRect(m_hero->getBox()))
            {
                AttackOnce = 0;
                if (getposition().x > m_hero->getposition().x)
                    m_hero->beingAttack(1, 3);
                else
                    m_hero->beingAttack(0, 3);
            }
        }
    }
}

void Pig::isover()
{
    is_over = 1;
}


void Pig::die()
{
    alive = 0;
    this->stopAllActions();
    auto dieSprite = Sprite::create("Actor/Monster/pig_monster_dead.png");
    
    if (dieSprite == nullptr)
    {
        log("dead not available");
    }
    else
    {
        dieSprite->setPosition(mymonster->getPosition());
        this->getParent()->addChild(dieSprite,5);
    }
    mymonster->setVisible(false);
    //this->removeFromParentAndCleanup(true);

}



void Pig::AttackOver()
{
    be_Attack = 0;
}

void Pig::createPig(Vec2 position)
{
    Sprite* pmonster = Sprite::create("Actor/Monster/pig_monster1.png");
    if (pmonster == nullptr)
    {
        log("Actor/Monster/pig_monster1.png not found");
    }
    else
    {

        pmonster->setPosition(position);
        this->getParent()->addChild(pmonster, 4);
    }
    bindsprite(pmonster);
}

void Pig::wander()
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
    if (move_rest == 1)
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
            mymonster->setFlippedX(true);
            c_facing = left;
            if (banmove != 2)
                m_position.x -= m_speed;
            break;
        case 4:
            mymonster->setFlippedX(false);
            c_facing = right;
            if (banmove != 3)
                m_position.x += m_speed;
            break;
        }
        mymonster->setPosition(m_position);
    }
}

void Pig::RestAction()
{
    state = 0;
    mymonster->stopAllActions();
    mymonster->runAction(CallPigAction(0));
}
void Pig::MoveAction()
{
    state = 1;
    mymonster->stopAllActions();
    mymonster->runAction(CallPigAction(1));
}

void Pig::beingAttack()
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

void Pig::setbanmove(int ban)
{
    banmove = ban;
}