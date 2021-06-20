#ifndef _PAUSEMENU_H
#define _PAUSEMENU_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Scene/TableRoom.h"
#include "AudioEngine.h"
USING_NS_CC;
extern int  BackgroundMusicId;
extern bool IsMusic;
extern bool IsEffect;

class PauseMenu : public cocos2d::Scene 
{
public:
	bool init() override;

	void changeEffectEvent();

	void changeMusicEvent();

	static PauseMenu* create();

	void playClickEffect();
};

class DieMenu :public cocos2d::Scene
{
public:
	bool init() override;

	static DieMenu* create();
};
#endif