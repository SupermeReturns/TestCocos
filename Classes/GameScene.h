#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "BlankScene.h"
#include "GameConfig.h"
#include "EndLayer.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : private BlankScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

};

#endif // __HELLOWORLD_SCENE_H__
