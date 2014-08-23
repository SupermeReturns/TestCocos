#include "WelcomeScene.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = WelcomeScene::create();

    scene->addChild(layer);

    return scene;
}

bool WelcomeScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    return true;
}
