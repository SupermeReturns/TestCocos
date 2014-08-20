#ifndef __B2SPRITE_H__
#define __B2SPRITE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>



USING_NS_CC;

/// B2Sprite负责保存Sprite中Box2d的相关信息
class B2Sprite : public Sprite
{
public:
	B2Sprite():m_b2Body(NULL){}

	/// 使用一张图片进行初始化
	/// @param 图片的路径
	/// @return 成功返回true, 错误返回false
	bool initWithFile(const std::string &filename);

	/// 创造B2Sprite实例的静态工厂方法，并使用一张图片对其初始化
	/// @param 图片的路径
	/// @return 返回实例的链接
	static B2Sprite* create (const std::string &filename);

	/// 定义了private变量m_b2Body的访问器方法
	/// getB2Body()， setB2Body()用于访问sprite的Box2d刚体
	CC_SYNTHESIZE(b2Body*, m_b2Body, B2Body);   //物理世界的“物体”
};

#endif