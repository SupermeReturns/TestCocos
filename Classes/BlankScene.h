#ifndef __BLANK_SCENE_H__
#define __BLANK_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BlankScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  

	CREATE_FUNC(BlankScene);

protected:

	Size visibleSize;
	Point origin;

	virtual void onKeyReleased(EventKeyboard::KeyCode kc, Event* e);

private:

};

#endif
