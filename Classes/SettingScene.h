#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "GameConfig.h"
#include "BlankScene.h"
#include "cocos2d.h"

USING_NS_CC;

/// InfoPanel：显示游戏帮助信息面板
class InfoPanel: public Layer
{
public:
    /// 根据str初始化相应的面板
    virtual bool init(const char str[]);

    /// 静态工厂方法，根据str生成相应的面板
    static InfoPanel* create(const char str[]);
};

class SettingScene : private BlankScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(SettingScene);

private:
    /// “作者信息”的菜单项并点击时调用
    void authorInfo(Ref *pSender);

    /// “帮助信息”的菜单项并点击时调用
    void helpInfo(Ref *pSender);

    /// “版权信息”的菜单项并点击时调用
    void copyrightInfo(Ref *pSender);

    /// “主菜单”的菜单项并点击时调用
    void mainMenu(Ref *pSender);

    /// “音乐开关”被点中时调用
    bool MusicButton(Touch* touch, Event* event);

    /// 处理退出键的点击
    void onKeyReleased(EventKeyboard::KeyCode kc, Event *e);

    /// pause EventListener for main MenuItems(music button, helpinfo, author info)
    void pauseEventListeners();

    /// resume EventListener for main MenuItems
    void resumeEventListeners();

    /// 当前激活的面板（可以为作者面板或帮助信息面板）
    Layer* curPanel = NULL;

    /// music waithc
    Sprite* music_button = NULL;

    // MenuItem for help info button and author info button
    Menu* infoMenu = NULL;  
};

#endif
