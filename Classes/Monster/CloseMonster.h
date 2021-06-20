#ifndef _CloseMonster_H_
#define _CloseMonster_H_

#include "cocos2d.h"
#include "monster.h"

class Pig : public Monster
{
public:
    CREATE_FUNC(Pig)
    void update(float delta)override;

    void dash();

    void isover()override;

    void die()override;

    void AttackOver();

    void createPig(Vec2 position);

    void MoveAction()override;

    void RestAction()override;

    void wander()override;

    void beingAttack()override;

    void setbanmove(int ban)override;
protected:
    int m_speed = 1;

    int banmove = 4;
    int blood_v = 15;
    int attackrange = 100;
    int findrange = 400;
    int controltime = 0;
    int attacttime = 0;
    int orien = 1;//1��4�ֱ�ָ�����������ƶ�
    bool is_over = 1;
    bool be_Attack = 0;//������ʱֹͣ��������
    int damage = 3;
    bool AttackOnce = 1;
    int checktime = 0;
};
#endif