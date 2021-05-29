#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"
#include "AudioEngine.h"


class TitleScene : public cocos2d::Scene
{
public:


    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);



};

#endif 