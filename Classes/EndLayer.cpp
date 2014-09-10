/*
 * EndLayer.cpp
 *
 *  Created on: 2014年7月15日
 *      Author: SunDongliang
 */


#include "EndLayer.h"
#include <string>
#include <stdio.h>
#include "GameScene.h"
#include "GameLayer.h"

USING_NS_CC;

EndLayer*  EndLayer::createWithHeight(float height) {
    EndLayer *pRet = new EndLayer();
    if (pRet && pRet->initWithHeight(height)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool EndLayer::initWithHeight(float height) {
    //获取屏幕信息
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // initiate background image and set opacity of background
    Sprite* bg = Sprite::create(kBG_ENDLAYER_PATH);
    bg->setScale(visibleSize.height/bg->getContentSize().height);
    bg->setAnchorPoint(Point(0.5, 0.5));
    bg->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    bg->setOpacity(220);

    this->addChild(bg);

    // 从XML中读取成绩
    float heights[6];
    heights[1] = UserDefault::sharedUserDefault()->getFloatForKey("1", 0);
    heights[2] = UserDefault::sharedUserDefault()->getFloatForKey("2", 0);
    heights[3] = UserDefault::sharedUserDefault()->getFloatForKey("3", 0);
    heights[4] = UserDefault::sharedUserDefault()->getFloatForKey("4", 0);
    heights[5] = UserDefault::sharedUserDefault()->getFloatForKey("5", 0);

    //加入最新成绩，并重新排序
    bool isBreak = false;
    for (int i = 1; i <= 5; i++) {
        if (height > heights[i]) {
            for (int j = 5; j > i; j--)
                heights[j] = heights[j - 1];
            heights[i] = height;
            if (i == 1)
                isBreak = true;
            break;
        }
    }

    // 向XML中保存重新排序后的结果
    UserDefault::sharedUserDefault()->setFloatForKey("1", heights[1]);
    UserDefault::sharedUserDefault()->setFloatForKey("2", heights[2]);
    UserDefault::sharedUserDefault()->setFloatForKey("3", heights[3]);
    UserDefault::sharedUserDefault()->setFloatForKey("4", heights[4]);
    UserDefault::sharedUserDefault()->setFloatForKey("5", heights[5]);

    //判断是否得到新纪录，加载不同文字提示
    if (isBreak) {
        Label *font1 = Label::create("Congratulations!", "Marker Felt", 60);
        Label *font2 = Label::create("A New Record :", "Marker Felt", 60);
        char str[30];
        sprintf(str,"%.0f",height);
        Label *font3 = Label::create(str, "Marker Felt", 60);

        //设置各行字的位置
        font1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 200 + origin.y));
        font2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 150 + origin.y));
        font3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 100 + origin.y));

        this->addChild(font1);
        this->addChild(font2);
        this->addChild(font3);
    } else {
        Label *font1 = Label::create("Height :", "Marker Felt", 30);

        char str[10];
        sprintf(str,"%.0f",height);
        Label *font2 = Label::create(str, "Marker Felt", 60);

        Label *font3 = Label::create("Best Record :", "Marker Felt", 30);

        sprintf(str,"%.0f",heights[1]);
        Label *font4 = Label::create(str, "Marker Felt", 30);

        //设置各行字的位置
        font1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 200 + origin.y));
        font2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 150 + origin.y));
        font3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 100 + origin.y));
        font4->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + 60 + origin.y));

        this->addChild(font1);
        this->addChild(font2);
        this->addChild(font3);
        this->addChild(font4);

        // 播放游戏结束的音效
        if (kSOUND_ON)
        {
          SimpleAudioEngine::sharedEngine()->playEffect(kSX_FAIL);
        }

    }

    //加载菜单控件
    auto mMenu_1 = MenuItemImage::create(kBT_REPLAY_POS_PATH, kBT_REPLAY_NEG_PATH, CC_CALLBACK_1(EndLayer::onReplay, this));
    auto mMenu_2 = MenuItemImage::create(kBT_MENU_POS_PATH, kBT_MENU_NEG_PATH, CC_CALLBACK_1(EndLayer::onMenu, this));

    mMenu_1->setAnchorPoint(Point(0, 0));
    mMenu_2->setAnchorPoint(Point(1, 0));

    mMenu_1->setPosition(Point(origin.x, origin.y));
    mMenu_2->setPosition(Point(visibleSize.width + origin.x, origin.y));

    auto mMenu = Menu::create(mMenu_1, mMenu_2, NULL);
    mMenu->setPosition(Point(origin.x, origin.y));
    this->addChild(mMenu);
}

void EndLayer::onReplay(cocos2d::Ref *pSender) {
    Node* parent = this->getParent();
    parent->removeAllChildren();
    parent->addChild(GameLayer::create());
}

void EndLayer::onMenu(cocos2d::Ref *pSender) {
    Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);
}
