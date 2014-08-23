#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "BlankScene.h"
#include "cocos2d.h"

USING_NS_CC;

class MainScene : private BlankScene
{

public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	CREATE_FUNC(MainScene);

	void onKeyReleased(EventKeyboard::KeyCode, Event *e);

private:
	void Play(Ref *pSender);
	void Highscores(Ref *pSender);
	void Settings(Ref *pSender);
};

#endif // __HELLOWORLD_SCENE_H__
