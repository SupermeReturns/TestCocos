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

/// StickSprite 长方形（横与竖，横的可以当平台，竖的可以快速增加高度）。
/// 在掉下来之前会不停地旋转，点击之后定住，并且垂直下落
class StickSprite : public B2Sprite
{
public:
    	/// 创建StickSprite的静态工厂方法，获得一个初始化过的实例
	static StickSprite* create();

	/// 对于B2Sprite中的初始化方法的覆盖，使用一张图片对sprite进行初始化，并且添加不停旋转的动作
	/// @param filename图片的路径
	/// @return 成功返回true, 错误返回false
	bool init(const std::string &filename);

	/// 使用各种性质值对sprite的b2Body进行初始化
	/// @param world b2World的指针
	/// @return 成功返回true, 错误返回false
	virtual void initB2Body(b2World* world);
};

/// BombSprite 具有炸弹的性质，如果与Pivot之间碰撞则游戏结束
class BombSprite : public B2Sprite
{
public:
    	/// 创建BombSprite的静态工厂方法，获得一个初始化过的实例
	static BombSprite* create();

	/// 使用各种性质值对sprite的b2Body进行初始化
	/// @param world b2World的指针
	/// @return 成功返回true, 错误返回false
	virtual void initB2Body(b2World* world);
};
#endif
