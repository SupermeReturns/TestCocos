/*
 * UseBox.cpp
 *
 *  Created on: 2014年5月21日
 *      Author: SunDongliang
 */

#include "UseBox.h"
#include <string>
#include <vector>
#include <stdio.h>

// 记录obj与pivot碰撞时的初始信息
struct FixtureInfo
{                
    float32 objAngle;            //碰撞时, obj的angle
    float32 pivotAngle;            //碰撞时, pivot的angle
    b2Vec2 localPosition;        //碰撞时, obj的position
    void* userData;            //obj的指针
    FixtureInfo()
  {
        objAngle = 0;
        pivotAngle = 0;
        localPosition.Set(0,0);
        userData = NULL;
    }
};

Box2dHandler::~Box2dHandler()
{
    // 在Body对象被释放之前，释放Body中的b2Fixture的UserData指向的FixtureInFo
    FixtureInfo* fi;
    for (b2Fixture *f = pivotFixture->GetBody()->GetFixtureList(); f; f = f->GetNext())
    {
      fi = static_cast<FixtureInfo*>(f->GetUserData());
      CC_SAFE_DELETE(fi);
    }

    // 释放b2World和Debugdraw
    CC_SAFE_DELETE(m_debugDraw);
    CC_SAFE_DELETE(m_world);
}

bool Box2dHandler::init()
{
 if (! Node::init()) {
   return false;
 }
  b2Vec2 gravity;
  gravity.Set(0.0f, kGRAVITY);    //垂直向下

  m_world = new b2World(gravity);
  m_world->SetAllowSleeping(false);
  m_world->SetContinuousPhysics(true);
  m_world->SetContactListener(this);
  //====================================================================
  // setup DebugDraw
  //====================================================================
  m_debugDraw = new GLESDebugDraw( kPTM_RATIO );
  m_world->SetDebugDraw(m_debugDraw);
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  //flags += b2Draw::e_jointBit;
  //flags += b2Draw::e_aabbBit;
  //flags += b2Draw::e_pairBit;
  //flags += b2Draw::e_centerOfMassBit;
  m_debugDraw->SetFlags(flags);

  //====================================================================
  // setup ground box
  //====================================================================
  Size s = Director::sharedDirector()->getWinSize();
  float height = s.height;
  float width = s.width;

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0, 0);

  m_groundBody = m_world->CreateBody(&groundBodyDef);

  b2EdgeShape groundBox;
  // bottom
  groundBox.Set(b2Vec2(0,-kGROUNDBOX_PADDLE/kPTM_RATIO), b2Vec2(width/kPTM_RATIO, -kGROUNDBOX_PADDLE/kPTM_RATIO));
  m_groundBody->CreateFixture(&groundBox, 0);

  // left
  groundBox.Set(b2Vec2(0,(height-kGROUNDBOX_PADDLE)/kPTM_RATIO), b2Vec2(0,-kGROUNDBOX_PADDLE/kPTM_RATIO));
  m_groundBody->CreateFixture(&groundBox, 0);

  // right
  groundBox.Set(b2Vec2(width/kPTM_RATIO, (height-kGROUNDBOX_PADDLE)/kPTM_RATIO), b2Vec2(width/kPTM_RATIO,-kGROUNDBOX_PADDLE/kPTM_RATIO));
  m_groundBody->CreateFixture(&groundBox, 0);

   return true;
}

void Box2dHandler::addNewB2Sprite(B2Sprite* sprite)
{
  // call b2Sprite's initB2Body method
  sprite->initB2Body(m_world);

  // the new obj is still falling
  isObjFalling_ = true;
}

void Box2dHandler::update(float dt)
{
   for(b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
         //更新Sprite的位置
       if (b->GetUserData() != NULL) {
           // 条件成立可以过滤掉groundBox的Box
           B2Sprite* sprite = static_cast<B2Sprite*>(b->GetUserData());

           if( (sprite->getTag() == kOBJ_TAG) ||(sprite->getTag() == kBOMB_TAG)) {
               // 如果为kOBJ_TAG,只需要更新该body对应的sprite即可
               b2Vec2 pos = b->GetPosition();
               float rotation = - b->GetAngle() /  kONE_DIV_PAI;
               sprite->setPosition(ccp(pos.x * kPTM_RATIO, pos.y * kPTM_RATIO));
               sprite->setRotation(rotation);
           }
           else if (sprite->getTag() == kPIVOT_TAG){
             // 如果为kPIVOT_TAG,需要更新该pivot的每个fixture对应的B2Sprite
               for (b2Fixture *f = b->GetFixtureList(); f; f = f->GetNext()) {
                   FixtureInfo* info = static_cast<FixtureInfo*>(f->GetUserData());
                   B2Sprite* part = static_cast<B2Sprite*>(info->userData);
                   b2Vec2 pos = b->GetWorldPoint(info->localPosition);
                   float rotation = -(b->GetAngle() - info->pivotAngle + info->objAngle)/ kONE_DIV_PAI;
                   part->setPosition(ccp(pos.x * kPTM_RATIO, pos.y * kPTM_RATIO));
                   part->setRotation(rotation);
               }
           }
       }
   }
   m_world->Step(dt, kVELOCITY_ITERATIONS, kPOSITION_ITERATIONS);
   dealCollisions();
}

void Box2dHandler::draw(Renderer *renderer,const kmMat4 &transform,bool transformUpdated)
{
    Node::draw(renderer, transform, transformUpdated);

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();
    m_world->DrawDebugData();
    kmGLPopMatrix();
}

void Box2dHandler::BeginContact(b2Contact* contact)
{
  bool a_is_wall = (contact->GetFixtureA()->GetBody()->GetUserData() == NULL);
  bool b_is_wall = (contact->GetFixtureB()->GetBody()->GetUserData() == NULL);

  // 如果为GroudBox的碰撞
  if ( a_is_wall || b_is_wall )
  {
    B2Sprite* sp;
    if (a_is_wall)
      sp = static_cast<B2Sprite*>(contact->GetFixtureB()->GetBody()->GetUserData());
    else
      sp = static_cast<B2Sprite*>(contact->GetFixtureA()->GetBody()->GetUserData()); 

    if (sp->getTag() == kBOMB_TAG )
    {
      // if one object is a bomb_sprite, them add it to contacts and deal with it later
      m_contacts.insert(sp->getB2Body());
    }
    else
    {
      // if one object is a  not bomb_sprite, then end the game
      if (kSOUND_ON)
        SimpleAudioEngine::sharedEngine()->playEffect(kSX_CLASH);
      this->isEnd = true;
    }
    return;
  }

  // 如果为普通的碰撞
  B2Sprite* spa = static_cast<B2Sprite*>(contact->GetFixtureA()
       ->GetBody()->GetUserData());
  B2Sprite* spb = static_cast<B2Sprite*>(contact->GetFixtureB()
       ->GetBody()->GetUserData());

  int ta = spa->getTag();
  int tb = spb->getTag();

  // one object is a pivot
  if( (ta == kPIVOT_TAG) || (tb == kPIVOT_TAG) )
  {
      if (ta != kPIVOT_TAG)
         std::swap(spa, spb);

      // if one object is a bomb_sprite, then play explosion sound effect and end game
      if ((ta == kBOMB_TAG) || (tb == kBOMB_TAG) )
      { 
            if (kSOUND_ON)
            {
              SimpleAudioEngine::sharedEngine()->playEffect(kSX_EXPLODE);
            }
            this->isEnd = true;
      }
      else
      {
            if (kSOUND_ON)
            {
              SimpleAudioEngine::sharedEngine()->playEffect(kSX_CLASH);
            }
            m_contacts.insert(spb->getB2Body());
      }
  }
}

void Box2dHandler::dealCollisions()
{
    std::set<b2Body*>::iterator it;
    for(it = m_contacts.begin(); it != m_contacts.end(); ++it) {
      b2Body *objBody = *it;
      B2Sprite *objSprite = static_cast<B2Sprite*>(objBody->GetUserData());

      // 首先检查是否为BombSprite,如果是说明Bomb撞到了groundbox
      // 动作：则销毁body,并把sprite移掉，
      if (objSprite->getTag() == kBOMB_TAG)
      {
        m_world->DestroyBody(objBody);
        objSprite->setB2Body(NULL);
        objSprite->removeFromParent();
        this->isObjFalling_ = false;
        continue;
      }

      // 如果不是，说明只是普通的obj与pivot相撞
      // 动作：将其body和pviot body合并
      b2Body *pivotBody = pivotFixture->GetBody();
      b2Fixture *objFixture = objBody->GetFixtureList();
      b2PolygonShape *objShape = (b2PolygonShape*)(objFixture->GetShape());

      // 1.更新最高点的位置
      float newHeight = objBody->GetPosition().y;
      if (this->curHeight < newHeight)
      {
        this->curHeight = newHeight;
      }


      // 2.克隆出一个相同的fixture
      int32 m_count = objShape->GetVertexCount();
      b2Vec2 m_vertices[8];
      bool moveLayer = false;

      for (int i = 0; i < m_count; i++)
      {  //得到obj各个顶点的世界坐标
        m_vertices[i] = objBody->GetWorldPoint(objShape->GetVertex(i));
      }

      for (int i = 0; i < m_count; i++)   // 将世界坐标转换为本地坐标
      {
          m_vertices[i] = pivotBody->GetLocalPoint(m_vertices[i]);
      }
      b2PolygonShape newShape;
      newShape.Set( m_vertices, m_count);

      b2FixtureDef newShapeDef;
      newShapeDef.shape = &newShape;
      newShapeDef.density =objFixture->GetDensity();
      newShapeDef.friction = objFixture->GetFriction();
      newShapeDef.restitution = objFixture->GetRestitution();

      FixtureInfo *info = new FixtureInfo();
      info->localPosition = pivotBody->GetLocalPoint( objBody->GetPosition() );
      info->objAngle = objBody->GetAngle();
      info->pivotAngle = pivotBody->GetAngle();
      info->userData = objBody->GetUserData();
      newShapeDef.userData = info;    //记录碰撞时的各变量的初始值

      //销毁obj的body
      objSprite->setB2Body(pivotBody);
      m_world->DestroyBody(objBody);

      latestFixture = pivotBody->CreateFixture(&newShapeDef);

      // comfirm that new obj is not falling anymore
      isObjFalling_ = false;
    }
    m_contacts.clear();
}

void Box2dHandler::addPivot(B2Sprite* sprite) 
{
  this->addNewB2Sprite(sprite);
  pivotFixture = sprite->getB2Body()->GetFixtureList();

  // 记录碰撞时的各变量的初始值
  FixtureInfo *info = new FixtureInfo();
  info->localPosition.Set(0.0f, 0.0f);
  info->objAngle = 0.0f;
  info->pivotAngle = 0.0f;
  info->userData = sprite;
  pivotFixture->SetUserData(info);

  // 为Body添加Joint,模拟摩擦力
  b2RevoluteJointDef jointDef;
  jointDef.Initialize(pivotFixture->GetBody(), m_groundBody, pivotFixture->GetBody()->GetWorldCenter());
  jointDef.maxMotorTorque = kMAX_MOTOR_TORQUE;
  jointDef.motorSpeed = 0.0f;
  jointDef.enableMotor = true;
  jointDef.collideConnected = true;
  m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&jointDef);
}

void Box2dHandler::recycle(float heightOfGamePanel) 
{
    // 1.更新pivotFixture,销毁所有非pivot的Fixture，并解除附着的joint
  pivotFixture = latestFixture;
  latestFixture = NULL;

  std::vector<b2Fixture*> fv;
  for (b2Fixture *f = pivotFixture->GetBody()->GetFixtureList(); f; f = f->GetNext()) {
    if (f != pivotFixture) {
      fv.push_back(f);
      continue;
    }
  }

  FixtureInfo* fi;
  B2Sprite* sprite;
  std::vector<b2Fixture*>::iterator it;
  for (it = fv.begin(); it != fv.end(); it++) {
    fi = static_cast<FixtureInfo*>((*it)->GetUserData());
    sprite = static_cast<B2Sprite*>(fi->userData);
    sprite->removeFromParent();
    CC_SAFE_DELETE(fi);
    pivotFixture->GetBody()->DestroyFixture(*it);
  }

  // 标记新的pivot，使其能够再次辨识
  fi = static_cast<FixtureInfo*>(pivotFixture->GetUserData());
  sprite = static_cast<B2Sprite*>(fi->userData);
  sprite->setTag(kPIVOT_TAG);
  pivotFixture->GetBody()->SetUserData(sprite);

  // 移除掉原来的joint， 重新调整groundbox的位置，使其伴随pivotFixture上升
  m_world->DestroyJoint(m_joint);
  b2Vec2 b2Position = b2Vec2(0, -heightOfGamePanel/kPTM_RATIO );
  m_groundBody->SetTransform(b2Position, 0);

  // Body加入新的RevoluteJoint
  b2RevoluteJointDef jointDef;
  jointDef.Initialize(pivotFixture->GetBody(), m_groundBody, pivotFixture->GetBody()->GetWorldCenter());
  jointDef.maxMotorTorque = kMAX_MOTOR_TORQUE;
  jointDef.motorSpeed = 0.0f;
  jointDef.enableMotor = true;
  jointDef.collideConnected = true;
  m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&jointDef);
}

bool Box2dHandler::isGameEnded()
{
  return this->isEnd;
}

float Box2dHandler::getCurHeight()
{
  return this->curHeight * kPTM_RATIO;
}

float Box2dHandler::getPivotAngle()
{
  return (m_joint->GetJointAngle() / kONE_DIV_PAI);
}

bool Box2dHandler::isObjFalling()
{
  return isObjFalling_;
}