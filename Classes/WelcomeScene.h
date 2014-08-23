#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "BlankScene.h"
#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : private BlankScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(WelcomeScene);

private:
};

#endif // __HELLOWORLD_SCENE_H__
