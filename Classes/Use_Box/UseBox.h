#ifndef __USE_BOX_H__
#define __USE_BOX_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "B2Sprite.h"
#include "../GameConfig.h"
#include "GLES-Render.h"
#include <string>
#include <set>
#include <utility>

USING_NS_CC;

/// Box2dHandler负责物理世界的计算和同步
class Box2dHandler : public Node, public b2ContactListener
{
public:
    /// 创建Box2dHandler的静态工厂方法，获得一个初始化过的实例
    CREATE_FUNC(Box2dHandler);

    /// 对Box2dHandler进行初始化
    /// @return 初始化成功返回true,失败返回false
    virtual bool init();

    /// 回收在屏幕之外的B2Sprite
    /// @param 当前gamepanel的高度，用于决定那些Sprite需要被清除，以及GroundBox移动距离
    void recycle(float heightOfGamePanel);

    /// 绘画调试性的视图
    virtual void draw(Renderer *renderer,const kmMat4 &transform,bool transformUpdated);

    /// 更新物理世界的进度以及显示世界的同步
    /// 每次游戏循环都会调用
    void update(float dt);

    /// 在Box2d世界中添加一个的新的物体
    /// @param sprite 需要添加的B2Sprite
    /// @param density 添加物体的密度
    /// @param friction 物体表面的摩擦力系数
    /// @param restitution 物体的弹性系数
    void addNewB2Sprite(B2Sprite* sprite, double density=10.0f, float friction=0.3f, float restitution=0.0f);

    /// 在物理世界中加入底座，并创造一个Joint
    /// @param sprite 需要添加的B2Sprite
    /// @param density 添加物体的密度
    /// @param friction 物体表面的摩擦力系数
    /// @param restitution 物体的弹性系数
    void addPivot(B2Sprite* sprite, double density=10.0f,float friction=0.3f, float restitution=0.0f);

    /// 检测游戏是否结束
    /// @param 如果游戏结束，返回true，否则返回false
    bool isGameEnded();

    /// 碰撞检测（当碰撞刚开始时，会被自动调用）
    virtual void BeginContact(b2Contact* contact);

    /// 处理碰撞事件
    void dealCollisions();

    /// 返回当前最高点纵坐标
    /// @return 最高点纵坐标
    float getCurHeight();

    /// 返回Pivot的偏移角度
    /// @return pvito的偏移角度（返回度数而不是弧度）
    float getPivotAngle();

    /// 是否新放入的物体还在下落
    bool isObjFalling();

private:
    /// 创建的物理世界的指针
    b2World* m_world;

    /// 世界“界限”的指针
    b2Body* m_groundBody;

    /// 调试绘图专用
    GLESDebugDraw* m_debugDraw;

    /// 保存碰撞事件的容器
    std::set<b2Body*> m_contacts;

    /// 当前Pivot的最高点
    float curHeight = 0;

    /// 是否新放入的物体还在下落
    bool isObjFalling_ = false;

    /// 
    bool isEnd = false;
    b2Fixture *pivotFixture;
    b2Fixture *latestFixture;
    b2RevoluteJoint *m_joint;

    /// 析构函数，在Box2dHandler生命结束时回收内存
    /// 主要是回收FixtureInfo中的内存
    virtual ~Box2dHandler();
};

#endif
