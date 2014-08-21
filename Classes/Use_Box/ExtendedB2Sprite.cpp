#include "ExtendedB2Sprite.h"

IronSprite* IronSprite::create()
{
	IronSprite *s = new IronSprite();
	if (s && s->init(IRON_PIC_PATH))
	{
		s->setScale(IRON_SCALE, IRON_SCALE);
		s->autorelease();
		return s;
	}
	delete s;
	return NULL;
}

void IronSprite::initB2Body(b2World* world)
{
	B2Sprite::initB2Body(world, IRON_DENSITY, IRON_FRICTION, IRON_RESTITUTION);
}




CuttonSprite* CuttonSprite::create()
{
	CuttonSprite *s = new CuttonSprite();
	if (s && s->init(CUTTON_PIC_PATH))
	{
		s->setScale(CUTTON_SCALE, CUTTON_SCALE);
		s->autorelease();
		return s;
	}
	delete s;
	return NULL;
}

void CuttonSprite::initB2Body(b2World* world)
{
	B2Sprite::initB2Body(world, CUTTON_DENSITY, CUTTON_FRICTION, CUTTON_RESTITUTION);	
}





BrickSprite* BrickSprite::create()
{
	BrickSprite *s = new BrickSprite();
	if (s && s->init(BRICK_PIC_PATH))
	{
		s->setScale(BRICK_SCALE, BRICK_SCALE);
		s->autorelease();
		return s;
	}
	delete s;
	return NULL;
}

void BrickSprite::initB2Body(b2World* world)
{
	return B2Sprite::initB2Body(world, BRICK_DENSITY, BRICK_FRICTION, BRICK_RESTITUTION);
}