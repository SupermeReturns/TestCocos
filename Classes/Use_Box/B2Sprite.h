#ifndef __B2SPRITE_H__
#define __B2SPRITE_H__

#include "GameConfig.h"
#include <string>
#include "cocos2d.h"
#include "Box2D/Box2D.h"


USING_NS_CC;

/// B2Sprite负责保存Sprite中Box2d的相关信息
class B2Sprite : public Sprite
{
public:
	B2Sprite():m_b2Body(NULL){}

	/// 使用一张图片对sprite进行初始化
	/// @param filename图片的路径
	/// @return 成功返回true, 错误返回false
	bool init(const std::string &filename);

	/// 创造B2Sprite实例的静态工厂方法，并使用一张图片对其初始化
	/// @param filename图片的路径
	/// @return 返回实例的指针
	static B2Sprite* create (const std::string &filename = kDEFAULT_PIC_PATH);

	/// 定义了private变量m_b2Body的访问器方法
	/// getB2Body()， setB2Body()用于访问sprite的Box2d刚体
	CC_SYNTHESIZE(b2Body*, m_b2Body, B2Body);   //物理世界的“物体”

	/// 用于对sprite的b2Body进行初始化
	/// 在派生类型继承时被覆盖
	/// @param b2World的指针
	virtual void initB2Body(b2World* world);

	/// 使用各种性质值对sprite的b2Body进行初始化
	/// @param world b2World的指针
	/// @param density 密度
	/// @param friction 摩擦力
	/// @param restitution 弹性
	/// @return 成功返回true, 错误返回false
	void initB2BodyWithParams(b2World* world, double density, float friction, float restitution);
};

#endif