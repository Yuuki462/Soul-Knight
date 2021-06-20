#ifndef _Monster_H_
#define _Monster_H_
#include "cocos2d.h"
#include "player\Hero.h"
using namespace cocos2d;
class Monster : public Node
{
public:
    CREATE_FUNC(Monster)

        //bool init()override;

    virtual void MoveAction();

    virtual void RestAction();

    void update(float delta)override;

    void bindsprite(Sprite* sprite);

    int getBlood_v();

    virtual Vec2 getposition();

    void setfacing();

    void bindhero(Hero* hero);

    virtual void wander();

    void track();

    int getdistance();

    virtual void beingAttack();

    JumpTo* jump(Vec2 h_position);//雪人的跳跃动作，暂时放这

    virtual void isover();

    virtual void die();

    void AttackOver();

    Rect getBox();

    int checkalive();

    void createsnow(Vec2 position);

    Sprite* getSprite() { return mymonster; }

    virtual void setbanmove(int ban);
protected:
    int m_speed = 2;

    bool state = 0;//判断状态，0为rest，1为move

    Sprite* mymonster;

    Hero* m_hero;

    int x = 520;

    int y = 520;

    enum facing { left, right };

    facing c_facing = right;

    int blood_v = 12;

    int attackrange = 200;

    int findrange = 500;

    int controltime = 0;

    int attacttime = 0;

    int move_rest = 0;//0和1分别指休息和移动

    int orien = 1;//1到4分别指向上下左右移动

    bool is_over = 0;//判断攻击动作是否完成

    bool be_Attack = 0;

    bool alive = 1;//判断是否活着

    bool is_attacking;//判断是否正在执行攻击动作

    int damage = 3;

    int banmove = 4;
};




#endif