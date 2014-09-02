/*
 * GameLayer.cpp
 *
 *  Created on: 2014年7月15日
 *      Author: SunDongliang
 */

#include "GameLayer.h"
#include "Use_Box/ExtendedB2Sprite.h"
#include "EndLayer.h"

USING_NS_CC;


bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	if (curObj == NULL)
		return false;
	curObj->stopAllActions();
	bh->addNewB2Sprite(curObj);
	this->curObj = NULL;

	return true;
}

void GameLayer::addNewObj() 
{

	// 根据比例产生随机数，从而决定下一个物体的类型, 设置物块的标签，大小，位置
	this->curObj = this->gc->NewRandomObj();
	curObj->setPosition(Point(visibleSize.width / 6, visibleSize.height / 6 * 5 - this->gamePanel->getPositionY()));
	this->gamePanel->addChild(curObj);

	// 设置物块的动作
	float t = 1.5 - this->gc->getCount() * 0.05;
	auto a1 = MoveBy::create(t, Point(visibleSize.width / 6 * 4, 0));
	auto a2 = MoveBy::create(t, Point(-visibleSize.width / 6 * 4, 0));
	auto slides = Sequence::create(a1, a2, NULL);
	auto sf = RepeatForever::create(slides);

	curObj->runAction(sf);
}

void GameLayer::addNewObjAfterSomeTime(float dt)
{
	this->addNewObj();
}

bool GameLayer::init() 
{
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	// 初始化gamePanel，并加入GameLayer中
    this->gamePanel = Layer::create();
    this->addChild(gamePanel);
	this->marker = Marker::create(visibleSize);
	gamePanel->addChild(marker);


	// 初始化gadgetPanel，并加入GameLayer中
	this->gadgetPanel = Layer::create();
	this->addChild(gadgetPanel);

	this->board = Dashboard::create();
	board->setPosition(Point(visibleSize.width / 2, visibleSize.height));
	gadgetPanel->addChild(board);

    // 每次游戏循环更新都会调用update函数
    this->scheduleUpdate();

    // 初始化游戏难度控制器
    this->gc = new GameController();

    // set up box2d handler
    this->bh = Box2dHandler::create();
    this->gamePanel->addChild(bh);

	// 在gamePanel中添加底座Pivot
	B2Sprite *pivot = BrickSprite::create();
	pivot->setTag(kPIVOT_TAG);
	pivot->setPosition( Point(visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y) );
	this->gamePanel->addChild(pivot);
	bh->addPivot(pivot);

	// 添加悬浮的平衡木
    this->addNewObj();

    // 设置触摸事件监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void GameLayer::cleanScreen() 
{
	// 确认Layer停止了移动
	this->isLayerMoving = false;

	// 回收内存空间
	bh->recycle(this->gamePanel->getPositionY());
}

void GameLayer::update(float delta)
{
	// Box2d的物理世界进行更新
	this->bh->update(delta);

	if (this->isEnded)
	{
		return;
	}

	// 检测游戏是否结束
	if (this->bh->isGameEnded())	
	{
		// 取消与GameLayer相关联的事件监听
		_eventDispatcher->removeEventListenersForTarget(this);

		// 创建EndLayer
		this->getParent()->addChild(EndLayer::createWithHeight(this->bh->getCurHeight()));

		this->isEnded = true;
		return;
	}

	// 检测是否需要移动画面,如果碰撞物体高度低于屏幕中线则返回false
	if (!this->isLayerMoving)
	{ 
		float middleLineHeight = visibleSize.height / 2 - this->gamePanel->getPositionY();
		if (this->bh->getCurHeight() > middleLineHeight)
		{
			this->isLayerMoving = true;
			// 为Layer创建动作：移动Layer，清理屏幕（屏幕外的Sprite）,添加新的Obj
			auto layer_move = MoveTo::create( 2, Point(0, -(this->bh->getCurHeight() - 100)) );
			//auto layer_move = MoveTo::create( 2, Point(0, -(this->bh->getCurHeight() - 5)) );
			auto  clean_screen= CallFunc::create(this, callfunc_selector(GameLayer::cleanScreen) );

			auto sq  = Sequence::create(layer_move, clean_screen, NULL);
			this->gamePanel->runAction(sq);
		}
	}

	// 更新小部件的状态（dashboard,marker）
	this->marker->update(this->bh->getCurHeight());
	this->board->update(this->bh->getPivotAngle());

	// 检测是否需要添加新的物块
	if (this->curObj == NULL)
	{
		if (!this->bh->isObjFalling())
		{
			if ( !this->isLayerMoving )
			{
				this->addNewObj();
			}
		}
	}
}

GameLayer::~GameLayer()
{
	delete this->gc;
}