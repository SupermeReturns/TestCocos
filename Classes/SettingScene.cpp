#include "SettingScene.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = SettingScene::create();

    scene->addChild(layer);

    return scene;
}

bool SettingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	this->setKeypadEnabled(true);

    return true;
}
