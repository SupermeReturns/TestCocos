#include "GameScene.h"
#include "GameLayer.h"
#include "cocos2d.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

GameScene::~GameScene()
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kMC_OTHERSCENE, true);
    }
}
Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !BlankScene::init() )
    {
        return false;
    }
    
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kMC_GAMESCENE, true);
    }
    this->setKeypadEnabled(true);

    Layer* l = GameLayer::create();
    l->setTag(kGAMELAYER_TAG);

    this->addChild(l);

    return true;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode kc, Event *e)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);       
    }

    if(kc == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        if (this->getChildByTag(kENDLAYER_TAG) == NULL)
        {
            Node* cp = this->getChildByTag(kCOMFIRM_PANEL_TAG);
            Node* gl = this->getChildByTag(kGAMELAYER_TAG);
            if (cp == NULL)
            {
                Layer* qg = QuitGame::create();
                qg->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
                qg->setTag(kCOMFIRM_PANEL_TAG);
                this->addChild(qg);
                _eventDispatcher->pauseEventListenersForTarget(gl);
            }
            else
            {
                this->removeChildByTag(kCOMFIRM_PANEL_TAG);
                _eventDispatcher->resumeEventListenersForTarget(gl);
            }
        }
        else
        {
            Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);
        }
    }
}