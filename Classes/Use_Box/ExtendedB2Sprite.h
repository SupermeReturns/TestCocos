#ifndef __EXTENDEDB2SPRITE_H__
#define __EXTENDEDB2SPRITE_H__

#include "B2Sprite.h"
#include "Box2D/Box2D.h"
#include "GameConfig.h"

/// IronSprite 具有铁一样的质量
class IronSprite : public B2Sprite
{
public:
    /// 创建IronSprite的静态工厂方法，获得一个初始化过的实例
	static IronSprite* create();

	/// 使用各种性质值对sprite的b2Body进行初始化
	/// @param world b2World的指针
	/// @return 成功返回true, 错误返回false
	virtual void initB2Body(b2World* world);
};

/// CuttonSprite 具有棉花一样的重量
class CuttonSprite : public B2Sprite
{
public:
    /// 创建CuttonSprite的静态工厂方法，获得一个初始化过的实例
	static CuttonSprite* create();

	/// 使用各种性质值对sprite的b2Body进行初始化
	/// @param world b2World的指针
	/// @return 成功返回true, 错误返回false
	virtual void initB2Body(b2World* world);
};

/// BrickSprite 具有普通砖块的重量
class BrickSprite : public B2Sprite
{
public:
    /// 创建BrickSprite的静态工厂方法，获得一个初始化过的实例
	static BrickSprite* create();

	/// 使用各种性质值对sprite的b2Body进行初始化
	/// @param world b2World的指针
	/// @return 成功返回true, 错误返回false
	virtual void initB2Body(b2World* world);
};

#endif
