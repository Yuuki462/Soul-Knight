#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "TableRoom.h"
#include "ui/CocosGUI.h"


class TitleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);

    void menuStartCallback(cocos2d::Ref* pSender);


};

#endif 