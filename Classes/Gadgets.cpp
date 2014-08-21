/*
 * Gadgets.cpp
 *
 *  Created on: 2014年7月20日
 *      Author: SunDongliang
 */

#include <String>
#include "Gadgets.h"

USING_NS_CC;

Marker* Marker::create(Size visibleSize) {
	Marker *pRet = new Marker();
	if (pRet && pRet->init(visibleSize)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Marker::init(Size visibleSize){
	if (!Layer::init()) {
		return false;
	}

	m_line = Sprite::create("line.png");
	m_font = Label::create("Height:    0", "Marker Felt", 30);
	m_line->setPosition(Point(visibleSize.width / 2, 0));
	m_font->setPosition(Point(visibleSize.width / 6, 20));

	addChild(m_line);
	addChild(m_font);
}

void Marker::update(float height) {
	if (height <= m_height)
		return;
	m_height = height;

	//停止当前所有动作
	m_line->stopAllActions();
	m_font->stopAllActions();

	//action for line:移动
	auto line_move = MoveTo::create( 1, Point(m_line->getPositionX(), height) );

	m_line->runAction(line_move);

	//action for font : 移动， 渐退，更新显示，渐显
	auto font_move = MoveTo::create( 1, Point(m_font->getPositionX(), height + 20) );
	FadeOut *fadeout = FadeOut::create(0.5);
	auto update_font = CallFunc::create(this, callfunc_selector(Marker::updateFont) );
	FadeIn *fadein = FadeIn::create(0.5);

	auto fontSeq  = Sequence::create(font_move, fadeout, update_font, fadein, NULL);
	m_font->runAction(fontSeq);
}

void Marker::updateFont() {
	//将label中的高度进行更新
	char str[10];
	sprintf(str,"%.0f",m_height);
	m_font->setString(	std::string("height:") + str );
}





Dashboard* Dashboard::create(float angle, Size visibleSize) {
	Dashboard *pRet = new Dashboard();
	if (pRet && pRet->init(angle, visibleSize)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Dashboard::init(float angle, Size visibleSize) {
	if (!Layer::init()) {
		return false;
	}
	m_panel = Sprite::create("panel.jpg");
	m_pointer = Sprite::create("pointer.png");

	m_panel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6 * 5));
	m_pointer->setPosition(Point(visibleSize.width / 2, visibleSize.height / 6 * 5));

	m_panel->setScale(0.5);
	m_pointer->setScale(0.5);

    m_pointer->setRotation(angle);

	addChild(m_panel);
	addChild(m_pointer);
}

void Dashboard::update(float angle) {
    m_pointer->setRotation(angle);
}
