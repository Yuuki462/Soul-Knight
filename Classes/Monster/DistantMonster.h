
#ifndef __DISTANT_MONSTER_H__
#define __DISTANT_MONSTER_H__

#include "Monster.h"
#include "Item/MonsterBullet.h"
USING_NS_CC;
class CrawShoot : public Monster
{
public:

    CREATE_FUNC(CrawShoot);

    void MoveAction()override;

    void RestAction()override;

    void update(float dt) override;

    void creatCraw(Vec2 position);


    void wander()override;


    Vector<Bullet*> createBullet();

    void die()override;

    void beingAttack()override;

    void setbanmove(int ban)override;
    /*void attack();

    void MoveAction();

    void RestAction();

    Vec2 getposition();

    void track();

    int getdistance();

    void beingAttack();

    Rect getBox();

    bool checkalive();
    */
protected:
    float m_backUpDistance = 100.;
    int damage = 2;
    int blood_v = 10;
    int controltime = 0;
    int attacktime = 0;
    int orien = 1;
    bool move_rest = 0;
    int banmove = 4;
    Vector<Bullet*>m_vBullet;
};

class Boss : public Monster
{
public:

    CREATE_FUNC(Boss);


    void update(float dt) override;

    void creatBoss(Vec2 position);


    Vector<Bullet*> createBullet();

    void die()override;

    void beingAttack()override;
protected:

    float m_backUpDistance = 100.;
    int attacktime = 0;
    int blood_v = 100;
    Vector<Bullet*>boss_vBullet;

};
#endif // DISTANT_MONSTER_H
