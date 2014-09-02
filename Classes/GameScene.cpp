#include "GameScene.h"
#include "GameLayer.h"
#include "cocos2d.h"

USING_NS_CC;


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
	this->setKeypadEnabled(true);

    this->addChild( GameLayer::create() );
    return true;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode, Event *e)
{
    if(kc == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        this->addChild(QuitGame::create());
    }
}