#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"

#include "Item/Weapon.h"

using namespace cocos2d;
class Hero : public Node
{
    friend class HeroUI;
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

    int getSpeed();

    Vec2 getposition();

    Rect getBox();

    void setSpeed(int c_speed);

    bool getis_turn();

    void setWeapon(Weapon* pWeapon);

    void bindWeapon(Weapon* pWeapon);

    static Hero* getInstance();

    void createHero(Vec2 position);

    void addpicture();

    Weapon* getWeapon();

    Sprite* getSprite();

    void setname(std::string str);

    std::string getname();

    Rect getSwordBox();

    int MainWeapondamage();

    void setbanmove(int way);

    void createHero();

    void beingAttack(bool orient,int damage);//0为受到从左边的攻击，1为受到从右边的攻击

    void die();

    void shiftWeapon(Weapon*_weapon);

    void setBlood(int _blood);

    void setshield(int _shield);

    void setcoin(int _coin);

    int getcoin();

    void healShield();

    bool checkalive();

    void recoverBlood(int _blood);

    void setMaxShield(int _maxshield);

    int getMaxShield();
protected:
    int m_speed = 3;
    Sprite* mysprite;
    int x = 520;
    int y = 520;
    std::vector<bool>keypressed = std::vector<bool>(7, false);//0-6分别为上下左右
    bool being_move = false;
    enum facing { left,right };
    enum facing c_facing = right;
    int blood_v = 7;
    int maxblood = 7;
    int shield = 5;
    int maxshield = 5;
    bool is_turn = 0;
    int banmove = 4;
    static Hero* m_pPresentHero;
    Weapon* m_pWeapon;
    std::string name="0";
    int m_coin = 0;
    int healtime = 0;
    bool alive = 1;

};




#endif