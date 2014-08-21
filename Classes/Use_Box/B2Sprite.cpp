#include "B2Sprite.h"
#include "../GameConfig.h"

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

void B2Sprite::initB2Body(b2World* world, double density, float friction, float restitution)
{
  // add body to B2Sprite
  b2BodyDef spriteBodyDef;
  spriteBodyDef.type = b2_dynamicBody;

  spriteBodyDef.position.Set(this->getPosition().x / PTM_RATIO,
     this->getPosition().y / PTM_RATIO);
  spriteBodyDef.userData = this;

  m_b2Body = world->CreateBody(&spriteBodyDef);


  // add fixture to B2Body
  b2PolygonShape spriteShape;

  Size size = this->getContentSize();
  float scale = this->getScale();
  spriteShape.SetAsBox(size.width * scale / PTM_RATIO / 2, size.height * scale /  PTM_RATIO / 2);

  b2FixtureDef spriteShapeDef;
  spriteShapeDef.shape = &spriteShape;
  spriteShapeDef.density =density;
  spriteShapeDef.friction = friction;
  spriteShapeDef.restitution = restitution;

  m_b2Body->CreateFixture(&spriteShapeDef);
}

