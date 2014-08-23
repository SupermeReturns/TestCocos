#include "MainScene.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "HighscoresScene.h"

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
    CCLOG("Entering MainScene::init");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	auto mMenu_1 = MenuItemFont::create("Play", CC_CALLBACK_1(MainScene::Play, this));
	auto mMenu_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(MainScene::Highscores, this));
	auto mMenu_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(MainScene::Settings, this));

	//menu_items_1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4 * 3 + origin.y));
	//menu_items_2->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4 * 2+ origin.y));
	//menu_items_3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4 + origin.y));

	auto mMenu = Menu::create(mMenu_1, mMenu_2, mMenu_3, NULL);
	mMenu->alignItemsVertically();
	mMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(mMenu);

	this->setKeypadEnabled(true);

    return true;
}

void MainScene::Play(cocos2d::Ref *pSender)
{
	auto GamScn = GameScene::createScene();
	
	Director::getInstance()->pushScene(TransitionFlipX::create(1, GamScn));
}

void MainScene::Highscores(cocos2d::Ref *pSender)
{
	auto HsScn = HighscoresScene::createScene();
	
	Director::getInstance()->pushScene(TransitionFlipX::create(1, HsScn));
}

void MainScene::Settings(cocos2d::Ref *pSender)
{
	auto SetScn = SettingScene::createScene();
	
	Director::getInstance()->pushScene(TransitionFlipX::create(1, SetScn));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode kc, Event *e)
{
	if(kc == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
    	Director::getInstance()->end();
	}
}
