#include "PauseMenu.h"
int  BackgroundMusicId;
bool IsMusic;
bool IsEffect;

void normalizeButton(ui::Button* pBtn)
{
    static const Size kBtnContSize(30, 18);
    pBtn->setScale9Enabled(true);

    pBtn->setCapInsets(Rect(12, 12, kBtnContSize.width, kBtnContSize.height));
    pBtn->setContentSize(Size(100, 90));
}

bool PauseMenu::init() 
{

    const auto kVisibleSize = Director::getInstance()->getVisibleSize();

    auto pauseBoard = ui::Scale9Sprite::create("interface/ui_pause_board.png");
    pauseBoard->setCapInsets(Rect(6, 6, 79, 61));
    pauseBoard->setContentSize(Size(500, 400));
    pauseBoard->setPosition(kVisibleSize.width / 2, kVisibleSize.height / 2);
    this->addChild(pauseBoard, 0);

    auto garnish = ui::Scale9Sprite::create("interface/ui_garnish.png");
    auto hint = Label::createWithTTF("Paused", "Font/IRANYekanBold.ttf", 65.);
    const Vec2 kGarnishPos = { kVisibleSize.width / 2 + 65, kVisibleSize.height / 2 + 120 };
    garnish->setContentSize(Size(270, 100));
    garnish->setPosition(kGarnishPos);
    hint->setPosition(kGarnishPos);
    this->addChild(garnish, 1);
    this->addChild(hint, 2);

    auto resumeBtn = ui::Button::create("interface/ui_btn_default.png",
        "interface/ui_btn_default_pressed.png");
    auto resume = Sprite::create("interface/ui_resume.png");
    auto effectBtn = ui::Button::create("interface/ui_btn_default.png",
        "interface/ui_btn_default_pressed.png");
    auto effect = Sprite::create("interface/ui_aueffect.png");
    auto musicBtn = ui::Button::create("interface/ui_btn_default.png",
        "interface/ui_btn_default_pressed.png");
    auto music = Sprite::create("interface/ui_music.png");
    const float kYCenter = kVisibleSize.height / 2 - 130;
    const float kXCenter = kVisibleSize.width / 2;
    normalizeButton(resumeBtn);
    normalizeButton(effectBtn);
    normalizeButton(musicBtn);
    resumeBtn->setPosition(Vec2(kXCenter - 190, kYCenter));
    resume->setPosition(Vec2(kXCenter - 190, kYCenter));
    effectBtn->setPosition(Vec2(kXCenter + 65, kYCenter));
    effect->setPosition(Vec2(kXCenter + 65, kYCenter));
    musicBtn->setPosition(Vec2(kXCenter + 190, kYCenter));
    music->setPosition(Vec2(kXCenter + 190, kYCenter));
    

    resumeBtn->addClickEventListener([&](Ref*) {
        Director::getInstance()->resume();
        Director::getInstance()->popScene();
    });
    effectBtn->addClickEventListener([&](Ref*) { changeEffectEvent(); });

    musicBtn->addClickEventListener([&](Ref*) { changeMusicEvent(); });

    this->addChild(resumeBtn, 1); this->addChild(resume, 2);
    this->addChild(effectBtn, 1); this->addChild(effect, 2,88);
    this->addChild(musicBtn, 1);  this->addChild(music, 2,77);

    return true;
}

PauseMenu* PauseMenu::create()
{
    auto* pRet = new(std::nothrow) PauseMenu();
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


void PauseMenu::changeEffectEvent()
{
    if (IsEffect)
    {
        IsEffect = false;
        this->getChildByTag(88)->setColor(Color3B(20, 20, 20));
    }
    else
    {
        IsEffect = true;
        this->getChildByTag(88)->setColor(Color3B(240, 240, 240));
    }
    playClickEffect();
}

void PauseMenu::changeMusicEvent()
{
    playClickEffect();

    if (IsMusic) {
        IsMusic = false;
        this->getChildByTag(77)->setColor(Color3B(20, 20, 20));
        AudioEngine::pause(BackgroundMusicId);
    }
    else
    {
        IsMusic = true;
        this->getChildByTag(77)->setColor(Color3B(240, 240, 240));
        AudioEngine::resume(BackgroundMusicId);
    }
}

void PauseMenu::playClickEffect()
{
    if (IsEffect) {
        AudioEngine::play2d("Audio/fx_btn1.mp3");
    }
}


bool DieMenu::init()
{
    const auto kVisibleSize = Director::getInstance()->getVisibleSize();

    auto pauseBoard = ui::Scale9Sprite::create("interface/ui_pause_board.png");
    pauseBoard->setCapInsets(Rect(6, 6, 79, 61));
    pauseBoard->setContentSize(Size(430, 320));
    pauseBoard->setPosition(kVisibleSize.width / 2, kVisibleSize.height / 2);
    this->addChild(pauseBoard, 0);

    auto garnish = ui::Scale9Sprite::create("interface/ui_garnish.png");
    auto hint = Label::createWithTTF("YouDie", "Font/IRANYekanBold.ttf", 65.);
    const Vec2 kGarnishPos = { kVisibleSize.width / 2 + 65, kVisibleSize.height / 2 + 97 };
    garnish->setContentSize(Size(270, 100));
    garnish->setPosition(kGarnishPos);
    hint->setPosition(kGarnishPos);
    this->addChild(garnish, 1);
    this->addChild(hint, 2);

    auto homeBtn = ui::Button::create("interface/ui_btn_default.png",
        "interface/ui_btn_default_pressed.png");
    auto home = Sprite::create("interface/ui_home.png");
    const float kYCenter = kVisibleSize.height / 2 - 106;
    const float kXCenter = kVisibleSize.width / 2;
    normalizeButton(homeBtn);
    homeBtn->setPosition(Vec2(kXCenter, kYCenter));
    home->setPosition(Vec2(kXCenter, kYCenter));

    homeBtn->addClickEventListener([&](Ref*) {
        log("Going to start scene.");
        Director::getInstance()->replaceScene(TableRoom::create());
        });

    this->addChild(homeBtn, 1);   this->addChild(home, 2);


    return true;
}

DieMenu* DieMenu::create()
{
    auto* pRet = new(std::nothrow) DieMenu();
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