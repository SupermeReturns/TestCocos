/*
 * Gadgets.cpp
 *
 *  Created on: 2014年7月20日
 *      Author: SunDongliang
 */

#include "Gadgets.h"
#include <String>

USING_NS_CC;

// Implementations for class Marker
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
    m_font->setString(    std::string("height:") + str );
}




// Implementations for class Dashboard
Dashboard* Dashboard::create() {
    Dashboard *pRet = new Dashboard();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Dashboard::init() {
    if (!Layer::init()) {
        return false;
    }
    m_panel = Sprite::create(kPANEL_PATH);
    m_pointer = Sprite::create(kPOINTER_PATH);

    m_panel->setScale(0.5);
    m_pointer->setScale(0.5);

    // add panel in the right position
    m_panel->setAnchorPoint(Point(0.5, 1.0));
    addChild(m_panel);

      Size size = m_pointer->getContentSize();
      float scale = m_pointer->getScale();

      // add pointer in the right position
    m_pointer->setAnchorPoint(Point(0.5, 0.4));
    m_pointer->setPosition(Point(0, -size.height * scale * 0.6));

    m_pointer->setRotation(0);

    addChild(m_pointer);
}

void Dashboard::update(float angle) {
    m_pointer->setRotation(angle);
}



// Implementations for class ConfirmPanel
bool ConfirmPanel::initWithString(const char str[])
{
    if (!Layer::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* m_background_pic = Sprite::create(kCONFIRM_BACKGROUD_PATH);
    m_background_pic->setAnchorPoint(Point(0.5f, 0.5f));
    m_background_pic->setPosition(Point(0, 0));
    bg_size = m_background_pic->getContentSize();
    this->addChild(m_background_pic);

    Label* m_font = Label::create(str, "Marker Felt", 30);
    m_font->setAnchorPoint(Point(0.5f, 0.5f));
    m_font->setPosition(Point(0, -bg_size.height/10));

    this->addChild(m_background_pic);
    this->addChild(m_font);

    this->addMenu();

    return true;
}

void ConfirmPanel::addMenu()
{
    auto mMenu_item_yes = MenuItemImage::create(kBT_YES_POS_PATH, kBT_YES_NEG_PATH, CC_CALLBACK_1(ConfirmPanel::onYes, this));
    auto mMenu_item_no = MenuItemImage::create( kBT_NO_POS_PATH, kBT_NO_NEG_PATH, CC_CALLBACK_1(ConfirmPanel::onNo, this));

    mMenu_item_yes->setPosition(Point(bg_size.width / 5, 0));
    mMenu_item_no->setPosition(-Point(bg_size.width / 5, 0));

    auto mMenu = Menu::create(mMenu_item_yes, mMenu_item_no, NULL);
    mMenu->setPosition(0, -bg_size.height * 0.32f);
    this->addChild(mMenu);
}

void ConfirmPanel::onNo(Ref *pSender)
{
    _eventDispatcher->resumeEventListenersForTarget(this->getParent(),true);
    this->removeFromParent();
}

void ConfirmPanel::onYes(Ref *pSender)
{
    Director::getInstance()->popSceneWithTransition<TransitionFlipX>(1.0);
}



// Implementations for class QuitGame
QuitGame* QuitGame::create()
{
    QuitGame *pRet = new QuitGame();
    if (pRet && pRet->initWithString(kQUIT_GAME)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}



// Implementations for class QuitApp
QuitApp* QuitApp::create()
{
    QuitApp *pRet = new QuitApp();
    if (pRet && pRet->initWithString(kQUIT_APP)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void QuitApp::onYes(Ref *pSender)
{
        Director::getInstance()->end();
}

void QuitApp::addMenu()
{
    auto mMenu_item_yes = MenuItemImage::create(kBT_YES_POS_PATH, kBT_YES_NEG_PATH,  CC_CALLBACK_1(QuitApp::onYes, this));
    auto mMenu_item_no = MenuItemImage::create(kBT_NO_POS_PATH, kBT_NO_NEG_PATH, CC_CALLBACK_1(QuitApp::onNo, this));

    mMenu_item_yes->setPosition(Point(bg_size.width / 5, 0));
    mMenu_item_no->setPosition(-Point(bg_size.width / 5, 0));

    auto mMenu = Menu::create(mMenu_item_yes, mMenu_item_no, NULL);
    mMenu->setPosition(0, bg_size.height * 0.32f);
    this->addChild(mMenu);    
}