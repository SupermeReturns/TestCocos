#ifndef __HIGHSCORES_SCENE_H__
#define __HIGHSCORES_SCENE_H__

#include "BlankScene.h"
#include "cocos2d.h"

class ResultPanel: public cocos2d::Layer{
public:

    virtual bool init();
    CREATE_FUNC(ResultPanel);

private:

    /// 用户点击Reset菜单项时调用
    void onReset(cocos2d::Ref *pSender);

    /// 用户点击Menu菜单项时调用
    void onMenu(cocos2d::Ref *pSender);
};

class HighscoresScene : private BlankScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HighscoresScene);

private:

    /// 根据保存的比赛成绩显示界面
    void initInterface();
};

#endif
