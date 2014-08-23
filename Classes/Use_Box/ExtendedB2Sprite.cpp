#include "ExtendedB2Sprite.h"

IronSprite* IronSprite::create()
{
	IronSprite *s = new IronSprite();
	if (s && s->init(kIRON_PIC_PATH))
	{
		s->setScale(kIRON_SCALE, kIRON_SCALE);
		s->autorelease();
		return s;
	}
	delete s;
	return NULL;
}

void IronSprite::initB2Body(b2World* world)
{
	B2Sprite::initB2BodyWithParams(world, kIRON_DENSITY, kIRON_FRICTION, kIRON_RESTITUTION);
}




CuttonSprite* CuttonSprite::create()
{
	CuttonSprite *s = new CuttonSprite();
	if (s && s->init(kCUTTON_PIC_PATH))
	{
		s->setScale(kCUTTON_SCALE, kCUTTON_SCALE);
		s->autorelease();
		return s;
	}
	delete s;
	return NULL;
}

void CuttonSprite::initB2Body(b2World* world)
{
	B2Sprite::initB2BodyWithParams(world, kCUTTON_DENSITY, kCUTTON_FRICTION, kCUTTON_RESTITUTION);	
}
 




BrickSprite* BrickSprite::create()
{
	BrickSprite *s = new BrickSprite();
	if (s && s->init(kBRICK_PIC_PATH))
	{
		s->setScale(kBRICK_SCALE, kBRICK_SCALE);
		s->autorelease();
		return s;
	}
	delete s;
	return NULL;
}

void BrickSprite::initB2Body(b2World* world)
{
	return B2Sprite::initB2BodyWithParams(world, kBRICK_DENSITY, kBRICK_FRICTION, kBRICK_RESTITUTION);
}