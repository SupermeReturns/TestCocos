#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "BlankScene.h"
#include "cocos2d.h"

USING_NS_CC;

class GameScene : private BlankScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void onKeyReleased(EventKeyboard::KeyCode, Event *e);

};

#endif // __HELLOWORLD_SCENE_H__
