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

bool EndLayer::init() {
    return Layer::init();
}

EndLayer*  EndLayer::createWithHeight(float height) {
	EndLayer* layer = EndLayer::create();
	layer->initWithHeight(height);
	return layer;
}


void EndLayer::initWithHeight(float height) {
	//获取屏幕信息
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// 从XML中读取成绩
	float heights[6];
	heights[1] = UserDefault::sharedUserDefault()->getFloatForKey("1");
	heights[2] = UserDefault::sharedUserDefault()->getFloatForKey("2");
	heights[3] = UserDefault::sharedUserDefault()->getFloatForKey("3");
	heights[4] = UserDefault::sharedUserDefault()->getFloatForKey("4");
	heights[5] = UserDefault::sharedUserDefault()->getFloatForKey("5");

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
	}

	//加载菜单控件
	auto mMenu_1 = MenuItemFont::create("Replay", CC_CALLBACK_1(EndLayer::onReplay, this));
	auto mMenu_2 = MenuItemFont::create("Menu", CC_CALLBACK_1(EndLayer::onMenu, this));

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
