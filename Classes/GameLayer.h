/*
 * GameLayer.h
 *
 *  Created on: 2014年7月15日
 *      Author: SunDongliang
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
#include "Use_Box/UseBox.h"
#include "GameConfig.h"
#include "Gadgets.h"

USING_NS_CC;

class GameLayer: public Layer {
public:
	/// 初始化GameLayer的各个部分
    virtual bool init();

    /// 为GameLayer创建静态工厂的create函数
    CREATE_FUNC(GameLayer);

	/// 每次循环负责更新游戏状态(检测是否结束，是否需要移动画面)，更新小部件状态
	/// 每次游戏循环调用一次
	virtual void update(float delta);
	
private:

	/// 储存游戏状态，true表示游戏结束
	bool isEnded = false;

	/// 当前Gamepanel是否在移动
	bool isLayerMoving = false;

	/// 用于存放游戏中的主体
	Layer *gamePanel;

	/// 用于存放小部件（比如仪表盘，标记杆，不会直接参加用于中的计算）
	Layer *gadgetPanel;

	/// 小部件marker，dashboard的指针
	Marker *marker;
	Dashboard *board;

	/// 负责物理世界的计算
	Box2dHandler *bh;

	/// 当前正在悬浮的平衡木
	B2Sprite *curObj;

	/// 屏幕大小信息
	Point origin ;
	Size visibleSize;

	/// 清理屏幕外的Sprite，回收内存资源
	/// @warning 只能在移动Layer完成之后才能调用
	/// @return 如果需要移动Layer，则返回true，否则false
	void cleanScreen();

	/// 初始化gadgetPanel，并向其中添加Marker，Dashboard等小部件
	void initGadgetPanel();

	/// 手动添加新的物块到gamePanel中，并制定移动的方式
	void addNewObj();

	///  自动在一定时间之后添加新的物体到gamePanel(手动添加新的物体请调用addNewBrick())
	void addNewObjAfterSomeTime(float dt);

	///  当系统检测到触摸事件，会自动调用该方法
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

};

#endif /* GAMELAYER_H_ */
