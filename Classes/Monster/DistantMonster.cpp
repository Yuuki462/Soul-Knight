#include "DistantMonster.h"
USING_NS_CC;

Animate* CallCrawAction(bool rest_move)//0为rest，1为move
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrame* frame = NULL;

    Vector<SpriteFrame*> array;
    std::ostringstream osr;
    if (rest_move == 0)
    {

        array.pushBack(SpriteFrame::create("Actor/Monster/Y_craw_monster2.png", Rect(0, 0, 64, 60)));
        array.pushBack(SpriteFrame::create("Actor/Monster/Y_craw_monster6.png", Rect(0, 0, 64, 60)));

    }
    else
    {
        for (int i = 1; i <= 5; ++i) {
            osr << "Actor/Monster/Y_craw_monster" << i << ".png";
            frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
            if (frame == nullptr)
            {
                log("Actor/Monster/pig_monster%d.png", i);
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

void CrawShoot::creatCraw(Vec2 position)
{
    Sprite* pmonster = Sprite::create("Actor/Monster/Y_craw_monster1.png");
    if (pmonster == nullptr)
    {
        log("Actor/Monster/Y_craw_monster1.png not found");
    }
    else
    {
        pmonster->setPosition(position);
        this->getParent()->addChild(pmonster, 4);
    }
    bindsprite(pmonster);
}

void CrawShoot::wander()
{
    auto m_position = mymonster->getPosition();

    //防止快速抽搐
    if (controltime == 50)
        controltime = 0;
    if (controltime == 0)
    {
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
                m_position.y++;
            break;
        case 2:
            if (banmove != 1)
                m_position.y--;
            break;
        case 3:
            
            mymonster->setFlippedX(true);
            c_facing = left;
            if (banmove != 2)
            {
                m_position.x--;
            }
            break;
        case 4:

            mymonster->setFlippedX(false);
            c_facing = right;
            if (banmove != 3)
            {
                m_position.x++;
            }
            break;
        }
        mymonster->setPosition(m_position);
    }
}

void CrawShoot::RestAction()
{
    state = 0;
    mymonster->stopAllActions();
    mymonster->runAction(CallCrawAction(0));
}

void CrawShoot::MoveAction()
{
    state = 1;
    mymonster->stopAllActions();
    mymonster->runAction(CallCrawAction(1));
}

Vector<Bullet*> CrawShoot::createBullet()
{
    Vector<Bullet*> vBullet;
    for (int i = 0; i < 5; i++) {
        vBullet.pushBack(MonsterBullet::create());
    }
    return vBullet;
}

void CrawShoot::update(float delta)
{
    if (alive && m_hero->checkalive() && m_hero != nullptr)
    {
        attacktime++;
        if (attacktime == 200)
        {
            m_vBullet = this->createBullet();
            for (int j = 0; j < m_vBullet.size(); j++) {
                this->getParent()->addChild(m_vBullet.at(j));
                m_vBullet.at(j)->attack(getposition(), 1, Vec2(0, 0));
            }
            attacktime = 0;
        }
        else
        {
            controltime++;
            wander();
        }
    }
    for (int j = 0; j < m_vBullet.size(); j++)
    {
        auto actionRemove = RemoveSelf::create();
        if (abs((m_vBullet.at(j))->getPosition().x) > 3000 && abs((m_vBullet.at(j))->getPosition().y) > 3000) {
            (m_vBullet.at(j))->getSprite()->runAction(actionRemove);
            (m_vBullet.at(j))->removeFromParentAndCleanup(true);
            m_vBullet.eraseObject(m_vBullet.at(j));
            continue;
        }
        if (m_vBullet.at(j) != nullptr&&m_hero!=nullptr && m_hero->checkalive())
        {
            auto monsterRect = m_hero->getSprite()->getBoundingBox();
            auto bulletRect = (m_vBullet.at(j))->getSprite()->getBoundingBox();
            /*auto p = (*iter)->getSprite()->getPosition();
            auto rect = monster->getBoundingBox();*/

            if (bulletRect.intersectsRect(monsterRect))
            {
                auto actionRemove = RemoveSelf::create();

                log("yes");
                m_hero->beingAttack(1,2);


                (m_vBullet.at(j))->getSprite()->runAction(actionRemove);
                (m_vBullet.at(j))->removeFromParentAndCleanup(true);
                m_vBullet.eraseObject(m_vBullet.at(j));
                //if (!m_vMonster.at(i)->checkalive())
                //{
                //    m_vMonster.at(i)->getSprite()->runAction(actionRemove);
                //    m_vMonster.at(i)->removeAllChildrenWithCleanup(true);
                //    m_vMonster.eraseObject(m_vMonster.at(i));
                //}
            }
        }

            
        
    }
}


void CrawShoot::die()
{
    alive = 0;
    this->stopAllActions();
    auto dieSprite = Sprite::create("Actor/Monster/Y_craw_monster_dead.png");

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

void CrawShoot::beingAttack()
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

void CrawShoot::setbanmove(int ban)
{
    banmove = ban;
}

void Boss::creatBoss(Vec2 position)
{
    Sprite* pmonster = Sprite::create("Actor/Monster/boss1.png");
    if (pmonster == nullptr)
    {
        log("Actor/Monster/boss1.png not found");
    }
    else
    {
        pmonster->setPosition(position);
        this->getParent()->addChild(pmonster, 4);
    }
    bindsprite(pmonster);
}

Vector<Bullet*> Boss::createBullet()
{
    Vector<Bullet*> vBullet;
    for (int i = 0; i < 7; i++) {
        vBullet.pushBack(BossBullet::create());
    }
    return vBullet;
}

void Boss::update(float delta)
{
    attacktime++;
    if (attacktime == 200)
    {
        boss_vBullet = this->createBullet();
        for (int j = 0; j < boss_vBullet.size(); j++) {
            this->getParent()->addChild(boss_vBullet.at(j));
            boss_vBullet.at(j)->attack(getposition(), 1, Vec2(0, 0));
        }
        attacktime = 0;
    }
    for (int j = 0; j < boss_vBullet.size(); j++)
    {
        auto actionRemove = RemoveSelf::create();
        if (abs((boss_vBullet.at(j))->getPosition().x) > 3000 && abs((boss_vBullet.at(j))->getPosition().y) > 3000) {
            (boss_vBullet.at(j))->getSprite()->runAction(actionRemove);
            (boss_vBullet.at(j))->removeFromParentAndCleanup(true);
            boss_vBullet.eraseObject(boss_vBullet.at(j));
            continue;
        }
        if (boss_vBullet.at(j) != nullptr && m_hero != nullptr&&m_hero->checkalive())
        {
            auto HeroRect = m_hero->getSprite()->getBoundingBox();
            auto bulletRect = (boss_vBullet.at(j))->getSprite()->getBoundingBox();
            /*auto p = (*iter)->getSprite()->getPosition();
            auto rect = monster->getBoundingBox();*/

            if (bulletRect.intersectsRect(HeroRect))
            {
                auto actionRemove = RemoveSelf::create();

                log("yes");
                m_hero->beingAttack(1, 3);


                (boss_vBullet.at(j))->getSprite()->runAction(actionRemove);
                (boss_vBullet.at(j))->removeFromParentAndCleanup(true);
                boss_vBullet.eraseObject(boss_vBullet.at(j));
                //if (!m_vMonster.at(i)->checkalive())
                //{
                //    m_vMonster.at(i)->getSprite()->runAction(actionRemove);
                //    m_vMonster.at(i)->removeAllChildrenWithCleanup(true);
                //    m_vMonster.eraseObject(m_vMonster.at(i));
                //}
            }
        }



    }
}

void Boss::beingAttack()
{
    be_Attack = 1;
    blood_v -= m_hero->MainWeapondamage();
    if (blood_v <= 0)
        die();
}

void Boss::die()
{
    alive = 0;
    auto dieSprite = Sprite::create("item/flame_effect1.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SpriteFrame* frame = NULL;

    Vector<SpriteFrame*> array;
    std::ostringstream osr;
    for (int i = 1; i <= 6; ++i) {
        osr << "item/flame_effect" << i << ".png";
        frame = SpriteFrame::create(osr.str(), Rect(0, 0, 64, 60));
        if (frame == nullptr)
        {
            log("item/flame_effect&d.png", i);
        }
        else
        {
            frame->setAnchorPoint(Vec2(0.5f, 0.f));
            array.pushBack(frame);
        }
        osr.str("");
    }
    auto animation = Animation::createWithSpriteFrames(array, 0.1f);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.2f);
    auto animate = Animate::create(animation);
    dieSprite->runAction(animate);
    if (dieSprite == nullptr)
    {
        log("item/flame_effect1.png");
    }
    else
    {
        dieSprite->setPosition(mymonster->getPosition());
        this->getParent()->addChild(dieSprite, 5);
    }
    mymonster->setVisible(false);
}

