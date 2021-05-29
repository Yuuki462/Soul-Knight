#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "Item/Gun.h"
//#include "Scene\TableRoom.h"

using namespace cocos2d;
class Hero : public Node
{
public:
    CREATE_FUNC(Hero)
    void MoveAction();
    void RestAction();
    void move();
    void update(float delta)override;
    void bindsprite(Sprite *sprite);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyreleased(EventKeyboard::KeyCode keyCode, Event* event);
    int getBlood_v();
    int getShield();
    Weapon* Hero::getWeapon();
    void Hero::bindWeapon(Weapon* weapon);
    void Hero::bindsword(Sprite* sword);//delate later
    void setSpeed(int c_speed);
    void setWeapon(Weapon* pWeapon);
    Sprite* getSprite();
    bool Hero::init() override;
protected:
    int m_speed = 3;
    Sprite* mysprite;
    Sprite* m_Sword;
    Weapon* m_pWeapon = nullptr;
    int x = 520;
    int y = 520;
    std::vector<bool>keypressed = std::vector<bool>(7, false);//0-6分别为上下左右
    bool being_move = false;
    enum facing { left,right };
    enum facing c_facing = right;
    int blood_v = 5;
    int shield = 5;
    
};




#endif