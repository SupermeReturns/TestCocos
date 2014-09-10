#include "MainScene.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "HighscoresScene.h"
#include "GameConfig.h"
#include "Gadgets.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // initiate background image
    Sprite* bg = Sprite::create(kBG_MAINSCENE_PATH);
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    Size bg_size = bg->getContentSize();
    bg->setScale(visibleSize.height/bg_size.height);
    this->addChild(bg);

    // initiate menu items
    auto mMenu_1 = MenuItemImage::create(kBT_PLAY_POS_PATH, kBT_PLAY_NEG_PATH, CC_CALLBACK_1(MainScene::Play, this));
    auto mMenu_2 = MenuItemImage::create(kBT_SCORE_POS_PATH, kBT_SCORE_NEG_PATH, CC_CALLBACK_1(MainScene::Highscores, this));
    auto mMenu_3 = MenuItemImage::create(kBT_SETTING_POS_PATH, kBT_SETTING_NEG_PATH, CC_CALLBACK_1(MainScene::Settings, this));

    auto mMenu = Menu::create(mMenu_1, mMenu_2, mMenu_3, NULL);
    mMenu->setTag(kMENU_TAG);
    mMenu->alignItemsVertically();
    mMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    this->addChild(mMenu);

    this->setKeypadEnabled(true);

    return true;
}

void MainScene::Play(cocos2d::Ref *pSender)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    auto GamScn = GameScene::createScene();
    
    Director::getInstance()->pushScene(TransitionFlipX::create(1, GamScn));
}

void MainScene::Highscores(cocos2d::Ref *pSender)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    auto HsScn = HighscoresScene::createScene();
    
    Director::getInstance()->pushScene(TransitionFlipX::create(1, HsScn));
}

void MainScene::Settings(cocos2d::Ref *pSender)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    auto SetScn = SettingScene::createScene();
    
    Director::getInstance()->pushScene(TransitionFlipX::create(1, SetScn));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode kc, Event *e)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);        
    }

    if(kc == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        if (this->getChildByTag(kCOMFIRM_PANEL_TAG) == NULL)
        {
            Layer* qa = QuitApp::create();
            qa->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
            qa->setTag(kCOMFIRM_PANEL_TAG);
            this->addChild(qa);
            _eventDispatcher->pauseEventListenersForTarget(this->getChildByTag(kMENU_TAG));
        }
        else
        {
            this->removeChildByTag(kCOMFIRM_PANEL_TAG);
            _eventDispatcher->resumeEventListenersForTarget(this->getChildByTag(kMENU_TAG));
        }
    }
}
