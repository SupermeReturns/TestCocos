#include "B2Sprite.h"

bool B2Sprite::init(const std::string &filename)
{
  return Sprite::initWithFile(filename);
}

B2Sprite* B2Sprite::create (const std::string &filename)
{
	B2Sprite *bs = new B2Sprite();
	if (bs && bs->init(filename))
	{
		bs->autorelease();
		return bs;
	}
	delete bs;
	return NULL;
}

void B2Sprite::initB2Body(b2World* world)
{
  initB2BodyWithParams(world, kDEFAULT_DENSITY, kDEFAULT_FRICTION, kDEFAULT_DENSITY);
}

void B2Sprite::initB2BodyWithParams(b2World* world, double density, float friction, float restitution)
{
  // add body to B2Sprite
  b2BodyDef spriteBodyDef;
  spriteBodyDef.type = b2_dynamicBody;

  spriteBodyDef.angle = this->getRotation() / (180 * kONE_DIV_PAI);
  spriteBodyDef.position.Set(this->getPosition().x / kPTM_RATIO,
     this->getPosition().y / kPTM_RATIO);
  spriteBodyDef.userData = this;

  m_b2Body = world->CreateBody(&spriteBodyDef);


  // add fixture to B2Body
  b2PolygonShape spriteShape;

  Size size = this->getContentSize();
  float scale = this->getScale();
  spriteShape.SetAsBox(size.width * scale / kPTM_RATIO / 2, size.height * scale /  kPTM_RATIO / 2);

  b2FixtureDef spriteShapeDef;
  spriteShapeDef.shape = &spriteShape;
  spriteShapeDef.density =density;
  spriteShapeDef.friction = friction;
  spriteShapeDef.restitution = restitution;

  m_b2Body->CreateFixture(&spriteShapeDef);
}

