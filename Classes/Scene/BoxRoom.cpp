#include "BoxRoom.h"

USING_NS_CC;

ui::Scale9Sprite* showInformation(const std::string& message)
{
    auto board = ui::Scale9Sprite::create("interface/voidboard.png");
    board->retain();
    board->setContentSize(Size(message.size() * 5.0f, 40.0f));

    
    auto setInformation = Label::createWithTTF(message, "Font/IRANYekanBold.ttf", 20.);

    const Vec2 informationPosition = { message.size() * 2.5f,25.0f };

    setInformation->setPosition(informationPosition);
    
    board->addChild(setInformation, 3);
    return board;
}

void normalize(ui::Button* pBtn)
{
    static const Size kBtnContSize(30, 18);
    pBtn->setScale9Enabled(true);

    pBtn->setCapInsets(Rect(12, 12, kBtnContSize.width, kBtnContSize.height));
    pBtn->setContentSize(Size(100, 90));
}

void M_normalize(Sprite* pBtn)
{
    static const Size kBtnContSize(30, 18);

    pBtn->setContentSize(Size(120, 120));
}
void W_normalize(Sprite* pBtn)
{
    static const Size kBtnContSize(30, 18);

    pBtn->setContentSize(Size(150, 70));
}
BoxRoom* BoxRoom::create()
{
    auto* pRet = new(std::nothrow) BoxRoom();
    if (pRet)
    {
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
    }
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BoxRoom::init()
{
    int x,y;
    for (int i = 0; i < 4; i++)
    {
        x = 120 + i * 330;
        auto pauseBoard = ui::Scale9Sprite::create("interface/ui_pause_board.png");
        pauseBoard->setCapInsets(Rect(6, 6, 79, 61));
        pauseBoard->setContentSize(Size(200, 300));
        pauseBoard->setPosition(x, 550);
        this->addChild(pauseBoard, 0);
    }
    for (int i = 0; i < 4; i++)
    {
        x = 120 + i * 330;
        auto pauseBoard = ui::Scale9Sprite::create("interface/ui_pause_board.png");
        pauseBoard->setCapInsets(Rect(6, 6, 79, 61));
        pauseBoard->setContentSize(Size(200, 300));
        pauseBoard->setPosition(x, 200);
        this->addChild(pauseBoard, 0);
    }
    Sprite* monster1 = Sprite::create("Actor/Monster/pig_monster1.png");
    Sprite* monster2 = Sprite::create("Actor/Monster/snow_monster_move1.png");
    Sprite* monster3 = Sprite::create("Actor/Monster/Y_craw_monster1.png");
    Sprite* monster4 = Sprite::create("Actor/Monster/boss1.png");
    Sprite* weapon1= Sprite::create("item/sword.png");
    Sprite* weapon2 = Sprite::create("item/spear.png");
    Sprite* weapon3 = Sprite::create("item/weapons.png");
    Sprite* weapon4 = Sprite::create("item/quickGun.png");
    M_normalize(monster1);
    M_normalize(monster2);
    M_normalize(monster3);
    M_normalize(monster4);
    W_normalize(weapon1);
    W_normalize(weapon2);
    W_normalize(weapon3);
    W_normalize(weapon4);
    monster1->setPosition(120, 550);
    monster2->setPosition(450, 550);
    monster3->setPosition(780, 550);
    monster4->setPosition(1110, 550);
    weapon1->setPosition(120, 200);
    weapon2->setPosition(450, 200);
    weapon3->setPosition(780, 200);
    weapon4->setPosition(1110, 200);
    this->addChild(monster1);
    this->addChild(monster2);
    this->addChild(monster3);
    this->addChild(monster4);
    this->addChild(weapon1);
    this->addChild(weapon2);
    this->addChild(weapon3);
    this->addChild(weapon4);

    ui::Scale9Sprite* m_pInformation1;
    m_pInformation1 = showInformation("Pig Monster");
    m_pInformation1->setPosition(120, 450);
    this->addChild(m_pInformation1);
    ui::Scale9Sprite* m_pInformation2;
    m_pInformation2 = showInformation("Snow Monster");
    m_pInformation2->setPosition(450, 450);
    this->addChild(m_pInformation2);
    ui::Scale9Sprite* m_pInformation3;
    m_pInformation3 = showInformation("Craw Monster");
    m_pInformation3->setPosition(780, 450);
    this->addChild(m_pInformation3);
    ui::Scale9Sprite* m_pInformation4;
    m_pInformation4 = showInformation("Boss");
    m_pInformation4->setPosition(1110, 450);
    this->addChild(m_pInformation4);
    ui::Scale9Sprite* m_pInformation5;
    m_pInformation5 = showInformation("Sword");
    m_pInformation5->setPosition(120, 100);
    this->addChild(m_pInformation5);
    ui::Scale9Sprite* m_pInformation6;
    m_pInformation6 = showInformation("Spear");
    m_pInformation6->setPosition(450, 100);
    this->addChild(m_pInformation6);
    ui::Scale9Sprite* m_pInformation7;
    m_pInformation7 = showInformation("HandGun");
    m_pInformation7->setPosition(780, 100);
    this->addChild(m_pInformation7);
    ui::Scale9Sprite* m_pInformation8;
    m_pInformation8 = showInformation("QuickGun");
    m_pInformation8->setPosition(1110, 100);
    this->addChild(m_pInformation8);

    auto resumeBtn = ui::Button::create("interface/ui_btn_default.png",
        "interface/ui_btn_default_pressed.png");
    auto resume = Sprite::create("interface/ui_resume.png");
    resumeBtn->setPosition(Vec2(620, 370));
    resume->setPosition(Vec2(620, 370));
    normalize(resumeBtn);
    this->addChild(resumeBtn, 2);
    this->addChild(resume, 3);
    resumeBtn->addClickEventListener([&](Ref*) {
        Director::getInstance()->resume();
        Director::getInstance()->popScene();
        });
	return true;
}