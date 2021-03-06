#include "HighscoresScene.h"
#include "GameConfig.h"

USING_NS_CC;

bool ResultPanel::init() {
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    this->setKeypadEnabled(true);


    // 从XML中读取成绩
    float heights[6];
    heights[1] = UserDefault::sharedUserDefault()->getFloatForKey("1", 0);
    heights[2] = UserDefault::sharedUserDefault()->getFloatForKey("2", 0);
    heights[3] = UserDefault::sharedUserDefault()->getFloatForKey("3", 0);
    heights[4] = UserDefault::sharedUserDefault()->getFloatForKey("4", 0);
    heights[5] = UserDefault::sharedUserDefault()->getFloatForKey("5", 0);

    // 显示成绩（前五名）
    Label *title = Label::create("Top Five", "Courier New", 60);
    title->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 6 * 5 + origin.y));
    this->addChild(title);

    char *(rank[]) = {"", "st", "nd", "rd", "th", "th"};
    if (false) {                      // 如果没有成绩,显示 Not available
        Label *font = Label::create("Not avaliable!", "Courier New", 50);

        font->setAnchorPoint(Point(0, 1));
        font->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 6 * 5 -  70 + origin.y));

        this->addChild(font);
    } else {                                  // 如果有成绩,显示成绩
        for (int i = 1; i <= 5;i++) {
            if (false)
                break;

            char str[30];
            sprintf(str,"%d%s  %.0f meters", i, rank[i], heights[i]);
            Label *font = Label::create(str, "Courier New", 50);

            font->setAnchorPoint(Point(0, 1));
            font->setPosition(Point(visibleSize.width / 10 + origin.x, visibleSize.height / 6 * 5 - i * 70 + origin.y));

            this->addChild(font);
        }
    }

    // 加载菜单控件
    auto mMenu_1 = MenuItemImage::create(kBT_RESET_POS_PATH, kBT_RESET_NEG_PATH, CC_CALLBACK_1(ResultPanel::onReset, this));
    auto mMenu_2 = MenuItemImage::create(kBT_MENU_POS_PATH, kBT_MENU_NEG_PATH, CC_CALLBACK_1(ResultPanel::onMenu, this));

    mMenu_1->setAnchorPoint(Point(0, 0));
    mMenu_2->setAnchorPoint(Point(1, 0));

    mMenu_1->setPosition(Point(origin.x, origin.y));
    mMenu_2->setPosition(Point(visibleSize.width + origin.x, origin.y));

    auto mMenu = Menu::create(mMenu_1, mMenu_2, NULL);
    mMenu->setPosition(Point(origin.x, origin.y));
    this->addChild(mMenu);


    return true;
}

void ResultPanel::onReset(cocos2d::Ref *pSender) {
    // play sound effect
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    // UserDefault中的成绩清零
    UserDefault::sharedUserDefault()->setFloatForKey("1", 0);
    UserDefault::sharedUserDefault()->setFloatForKey("2", 0);
    UserDefault::sharedUserDefault()->setFloatForKey("3", 0);
    UserDefault::sharedUserDefault()->setFloatForKey("4", 0);
    UserDefault::sharedUserDefault()->setFloatForKey("5", 0);

    //重新加载界面
    Node* parent = this->getParent();
    parent->removeChild(this);
    parent->addChild(ResultPanel::create());
}

void ResultPanel::onMenu(cocos2d::Ref *pSender) {
    // play sound effect
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_TOUCH);
    }

    Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);
}

Scene* HighscoresScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HighscoresScene::create();

    scene->addChild(layer);

    return scene;
}

bool HighscoresScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // initiate background image
    Sprite* bg = Sprite::create(kBG_SCORESCENE_PATH);
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    Size bg_size = bg->getContentSize();
    bg->setScale(visibleSize.height/bg_size.height);
    this->addChild(bg);

    this->setKeypadEnabled(true);

    this->addChild(ResultPanel::create());
    return true;
}
