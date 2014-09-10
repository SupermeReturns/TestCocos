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
 



bool StickSprite::init(const std::string &filename)
{
    if (!B2Sprite::init(filename))
    {
        return false;
    }
    this->setAnchorPoint(Point(0.5f, 0.5f));

    // StickSprite rotates forever before it is released!
    auto rotate = RotateBy::create(1.0, 360);
    auto r = RepeatForever::create(rotate);
    this->runAction(r);

    // rewind the sound effect of rotating stick
    if (kSOUND_ON)
    {
        sx_id = SimpleAudioEngine::sharedEngine()->playEffect(kSX_ROTATE, true);
    }

    return true;
}

StickSprite* StickSprite::create()
{
    StickSprite *s = new StickSprite();
    if (s && s->init(kSTICK_PIC_PATH))
    {
        s->setScale(kSTICK_SCALE, kSTICK_SCALE);
        s->autorelease();
        return s;
    }
    delete s;
    return NULL;
}

void StickSprite::initB2Body(b2World* world)
{
    // when it is dropped, stop the rotating sound effect
    if (kSOUND_ON)
    {
        SimpleAudioEngine::sharedEngine()->stopEffect(sx_id);
    }

    return B2Sprite::initB2BodyWithParams(world, kSTICK_DENSITY, kSTICK_FRICTION, kSTICK_RESTITUTION);
}





BombSprite* BombSprite::create()
{
    BombSprite *s = new BombSprite();
    if (s && s->init(kBOMB_PIC_PATH))
    {
        s->setScale(kBOMB_SCALE, kBOMB_SCALE);
        s->autorelease();
        return s;
    }
    delete s;
    return NULL;
}

void BombSprite::initB2Body(b2World* world)
{
    return B2Sprite::initB2BodyWithParams(world, kBOMB_DENSITY, kBOMB_FRICTION, kBOMB_RESTITUTION);
}
