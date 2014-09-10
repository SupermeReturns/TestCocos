/*
 * GameLayer.h
 *
 *  Created on: 2014年7月15日
 *      Author: SunDongliang
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "GameConfig.h"
 #include <time.h>
#include <stdlib.h>
#include "Gadgets.h"
#include "Use_Box/ExtendedB2Sprite.h"
#include "Use_Box/UseBox.h"
#include "cocos2d.h"

USING_NS_CC;

/// BGController负责背景的滚动显示
class BGController:public Layer
{
public:
    /// 每次滚动屏幕后调用
    /// @param 滚动后屏幕底部相对于游戏地图的高度
    void update(float screen_buttom);

    /// 初始化函数，载入滚动背景
    virtual bool init();

    /// 静态工厂方法
    CREATE_FUNC(BGController);
private:
    // 滚动的Sprite的指针
    Sprite *top;
    Sprite *mid;
    Sprite *but;

    /// 背景图片的缩放比例
    float bg_scale;
};

/// GameController 负责控制Obj的生成,调节游戏的难度
/// 随着游戏的进行，逐渐加大游戏的难度，提高高难度物体产生的几率，降低低难度物体产生的几率
class GameController
{
public:
    ///  初始化随机数等工作
    GameController()
    {
        count =0;
        cutton_possi = possi[0];
        brick_possi = cutton_possi+ possi[1];
        iron_possi = brick_possi + possi[2];
        stick_possi = iron_possi + possi[3];
        bomb_possi = stick_possi + possi[4];
    };

    /// 根据比例产生随机数，从而决定下一个物体的类型, 设置物块的标签，大小，位置，之后会调整几率
    B2Sprite* NewRandomObj()
    {
        B2Sprite* curObj;
        // 根据比例产生随机数，从而决定下一个物体的类型, 设置物块的标签，大小，位置
        srand((int)time(0));
        int r = rand() % 100;
        if (r < cutton_possi)
        {
            curObj = CuttonSprite::create();
            curObj->setTag(kOBJ_TAG);
        } else if (r < brick_possi) 
        {
            curObj = BrickSprite::create();
            curObj->setTag(kOBJ_TAG);            
        } else if (r < iron_possi)
        {
            curObj = IronSprite::create();
            curObj->setTag(kOBJ_TAG);
        } else if (r < stick_possi)
        {
            curObj = StickSprite::create();
            curObj->setTag(kOBJ_TAG);
        } else if (r < bomb_possi)
        {
            curObj = BombSprite::create();
            curObj->setTag(kBOMB_TAG);
        }

        this->count++;
        this->reset();
        return curObj;
    };
    
    int getCount(){
        return count;
    };
private:
    int  possi [5] = { kCUTTON_POSSIBILITY, kBRICK_POSSIBILITY, kIRON_POSSIBILITY, kSTICK_POSSIBILITY, kBOMB_POSSIBILITY}; 
    int cutton_possi , brick_possi, iron_possi, stick_possi, bomb_possi;
    int count;

    /// 调整物体产生几率
    /// 提高高难度物体产生的几率，降低低难度物体产生的几率
    void reset()
    {
        for (int i =0; i<5; i++)
        {
            if(possi[i] != 0)
            {
                if (i == 4)
                {
                    return;
                }
                possi[i] -= 1 ;
                possi[i+1] += 1;

                cutton_possi = possi[0];
                brick_possi = cutton_possi+ possi[1];
                iron_possi = brick_possi + possi[2];
                stick_possi = iron_possi + possi[3];
                bomb_possi = stick_possi + possi[4];
            }
        }
    };
};

class GameLayer: public Layer {
public:
    /// 初始化GameLayer的各个部分
    virtual bool init();

    /// 为GameLayer创建静态工厂的create函数
    CREATE_FUNC(GameLayer);

    /// 每次循环负责更新游戏状态(检测是否结束，是否需要移动画面)，更新小部件状态
    /// 每次游戏循环调用一次
    virtual void update(float delta);

    ~GameLayer();
    
private:
    /// 负责控制Obj的生成,调节游戏的难度
    GameController* gc;

    /// 负责控制背景的滚动显示
    BGController* bgc;

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

    /// 手动添加新的物块到gamePanel中，并制定移动的方式
    void addNewObj();

    ///  自动在一定时间之后添加新的物体到gamePanel(手动添加新的物体请调用addNewBrick())
    void addNewObjAfterSomeTime(float dt);

    ///  当系统检测到触摸事件，会自动调用该方法
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

};

#endif /* GAMELAYER_H_ */
