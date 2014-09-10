#include "SettingScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

// implementation for class InfoPanel
bool InfoPanel::init(const char str[])
{
    if (!Layer::init())
    {
        return false;
    }

    // initiate background image
    Sprite* bg = Sprite::create(kBG_INFOPANEL_PATH);
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setPosition(Point(0, 0));
    Size bg_size = bg->getContentSize();
    this->addChild(bg);

    // add info(lable)
    auto info = Label::create(str, "Marker Felt", 30);
    info->setPosition(Point(0, 0));
    this->addChild(info);
    return true;
}

InfoPanel* InfoPanel::create(const char str[])
{
    InfoPanel *pRet = new InfoPanel();
    if (pRet && pRet->init(str)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

// implementation for class SettingScene
Scene* SettingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingScene::create();
    scene->addChild(layer);
    return scene;
}

bool SettingScene::init()
{
    if ( !BlankScene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    this->setKeypadEnabled(true);

    // initiate background image
    Sprite* bg = Sprite::create(kBG_SETTINGSCENE_PATH);
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    Size bg_size = bg->getContentSize();
    bg->setScale(visibleSize.height/bg_size.height);
    this->addChild(bg);

    // initiate music switch
    if(kSOUND_ON)
        this->music_button = Sprite::create(kBT_MUSIC_POS_PATH);
    else
        this->music_button = Sprite::create(kBT_MUSIC_NEG_PATH);
    music_button->setAnchorPoint( Point(0.5, 0));
    music_button->setPosition(Point(visibleSize.width / 2, visibleSize.height / 10 * 7));
    this->addChild(music_button);

    // set up event listenner for music switch
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SettingScene::MusicButton, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, music_button);

    // initiate menu items
    auto mMenu_help = MenuItemImage::create(kBT_HELP_POS_PATH, kBT_HELP_NEG_PATH, CC_CALLBACK_1(SettingScene::helpInfo, this));
    auto mMenu_author = MenuItemImage::create(kBT_AUTHOR_POS_PATH, kBT_AUTHOR_NEG_PATH, CC_CALLBACK_1(SettingScene::authorInfo, this));
    auto mMenu_copyright = MenuItemImage::create(kBT_COPYRIGHT_POS_PATH, kBT_COPYRIGHT_NEG_PATH, CC_CALLBACK_1(SettingScene::copyrightInfo, this));    
    auto mMenu_main = MenuItemImage::create(kBT_MENU_POS_PATH, kBT_MENU_NEG_PATH, CC_CALLBACK_1(SettingScene::mainMenu, this));

    mMenu_help->setAnchorPoint(Point(0.5, 0));
    mMenu_author->setAnchorPoint(Point(0.5, 0));
    mMenu_copyright->setAnchorPoint(Point(0.5, 0));    
    mMenu_main->setAnchorPoint(Point(1.0, 0));

    mMenu_help->setPosition( Point(visibleSize.width / 2, visibleSize.height / 10 * 6) );
    mMenu_author->setPosition( Point(visibleSize.width / 2, visibleSize.height / 10 * 5) );
    mMenu_copyright->setPosition( Point(visibleSize.width / 2, visibleSize.height / 10 * 4) );
    mMenu_main->setPosition( Point(visibleSize.width + origin.x, origin.y) );

    infoMenu = Menu::create(mMenu_help, mMenu_author,  mMenu_copyright, NULL);
    auto mainMenu =  Menu::create(mMenu_main, NULL);

    infoMenu->setPosition(Point(0, 0));
    mainMenu->setPosition(Point(0, 0));

    this->addChild(infoMenu);
    this->addChild(mainMenu);
    return true;
}

void SettingScene::authorInfo(Ref *pSender)
{
    this->pauseEventListeners();
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    this->curPanel = InfoPanel::create(kAUTHOR_INFO);
    curPanel->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(curPanel);
}

void SettingScene::helpInfo(Ref *pSender)
{
    this->pauseEventListeners();

    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    this->curPanel = InfoPanel::create(kHELP_INFO);
    curPanel->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(curPanel);
}

void SettingScene::copyrightInfo(Ref *pSender)
{
    this->pauseEventListeners();

    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    this->curPanel = InfoPanel::create(kCOPYRIGHT_INFO);
    curPanel->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(curPanel);   
}

void SettingScene::mainMenu(Ref *pSender)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    UserDefault::sharedUserDefault()->setFloatForKey("kSOUND_ON", kSOUND_ON);
    Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);   
}

bool SettingScene::MusicButton(Touch* touch, Event* event)
{
    // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    //Get the position of the current point relative to the button
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    //Check the click area
    if (rect.containsPoint(locationInNode))
    {
        if (kSOUND_ON)
        {
            SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
        }

        if(kSOUND_ON)
        {
            target->setTexture(kBT_MUSIC_NEG_PATH);

            // puase background music
            SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        else
        {
            target->setTexture(kBT_MUSIC_POS_PATH);

            // start background music
            // if you use SimpleAudioEngine, it must resume here
            SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
        kSOUND_ON = !kSOUND_ON;

        return true;
    }
    return false;
}

void SettingScene::onKeyReleased(EventKeyboard::KeyCode kc, Event *e)
{
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    if(kc == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
        if (this->curPanel == NULL)
        {
            UserDefault::sharedUserDefault()->setFloatForKey("kSOUND_ON", kSOUND_ON);
            Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);   
            return;
        }

        this->removeChild(curPanel);
        this->resumeEventListeners();
        curPanel = NULL;
    }
}

void SettingScene::pauseEventListeners()
{
    _eventDispatcher->pauseEventListenersForTarget(this->music_button);
    _eventDispatcher->pauseEventListenersForTarget(this->infoMenu);
}

void SettingScene::resumeEventListeners()
{
    _eventDispatcher->resumeEventListenersForTarget(this->music_button,true);
    _eventDispatcher->resumeEventListenersForTarget(this->infoMenu);
}
