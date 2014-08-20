#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "BlankScene.h"

USING_NS_CC;

class SettingScene : private BlankScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(SettingScene);

private:
};

#endif
