#include "BlankScene.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* BlankScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = BlankScene::create();

    scene->addChild(layer);

    return scene;
}

bool BlankScene::init()
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

void BlankScene::onKeyReleased(EventKeyboard::KeyCode kc, Event *e)
{
    if (kSOUND_ON)
    {
    SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }
                
    if(kc == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);
    }
    else
    {
    }
}