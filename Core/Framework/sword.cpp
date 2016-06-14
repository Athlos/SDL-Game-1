#include "sword.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "Box2D.h"


#include <cassert>

Sword::Sword(Player& m_player)
: m_isAttacking(false)
, m_swordSprite(0)
, m_player(m_player)
, m_x(0.0f)
, m_y(0.0f)
{
	m_isAttacking = false;
	Entity::Entity();
	type = ClassType::BLANK;
}

Sword::~Sword()
{
}

void
Sword::Initialise(AnimatedSprite* swordSprite, b2World& world)
{
	//setting class type, for collision detection
	type = ClassType::SWORD;
	swordDirection = Direction::UP;
	m_isAttacking = false;

	assert(swordSprite);
	m_swordSprite = swordSprite;

	m_swordSprite->SetX(m_x);
	m_swordSprite->SetY(m_y);

	SetupCollision(world);
}

void
Sword::SetupCollision(b2World& world)
{
	type = ClassType::SWORD;
	m_swordBodyDef.type = b2_dynamicBody;
	//the position of the sword is set to be at the middle of the top area of the player (as a test)
	//this position is set here and then in the function for setting direction, for now it is done twice and will be fixed later on
	m_swordBodyDef.position.Set(m_player.GetPositionX(), m_player.GetPositionY());
	m_swordBodyDef.angle = 0;
	m_swordBody = world.CreateBody(&m_swordBodyDef);

	//sword triange collision polygon
	b2Vec2 vertices[3];
	//3 points on the screen
	vertices[0].Set(28.0f, 0);
	vertices[1].Set(56.0f, -48.0f);
	vertices[2].Set(0.0f, -48.0f);
	int32 count = 3;
	SetupSwordCollisionPolygon(m_player.GetPositionX(), m_player.GetPositionY(), vertices, 3, world);

	m_swordBody->GetFixtureList()->SetSensor(true);
	m_swordBody->SetUserData(this);
}

void
Sword::SetupSwordCollisionPolygon(float positionX, float positionY, b2Vec2 vertices[3], int32 count, b2World& world)
{
	//has to change based on direction
	m_swordBodyDef.position.Set(positionX, positionY);
	//setting the sword shape from the points above
	m_swordShape.Set(vertices, count);
	m_swordFixtureDef.shape = &m_swordShape;
	//setting the desntiy so the sword isn't moved around
	m_swordFixtureDef.density = 0;
	m_swordBody->CreateFixture(&m_swordFixtureDef);
	//setting an anchor point for the sword
	b2Vec2 anchorPoint = m_swordBody->GetPosition();
	//setting up what two bodies are to be welded together and at what point
	swordWeldToPlayer.bodyA = m_swordBody;
	swordWeldToPlayer.bodyB = m_player.GetPlayerBody();
	//making the sword collide with the player, not sure if this is really needed, but will leave in for now
	swordWeldToPlayer.collideConnected = true;
	//init the welded point
	swordWeldToPlayer.Initialize(m_swordBody, m_player.GetPlayerBody(), anchorPoint);
	world.CreateJoint(&swordWeldToPlayer);
}

void
Sword::Draw(BackBuffer& backBuffer)
{
	if (m_isAttacking)
	{
		//assert(m_swordSprite);
		m_swordSprite->Draw(backBuffer);
		//draw a red triangle where the collision should be
		//backBuffer.DrawDebug(shape, pos x, pos y);
		backBuffer.DebugDrawCollision(*m_swordBody, m_swordShape);
	}
}

void
Sword::Process(float deltaTime)
{
	//m_swordBody->SetTransform(b2Vec2(m_player.GetPositionX() + 22.0f, m_player.GetPositionY() + 6.0f), 0.0);
	m_x = m_swordBody->GetPosition().x + 22.0f;
	m_y = m_swordBody->GetPosition().y;
	m_swordSprite->SetX(m_swordBody->GetPosition().x + 22.0f);
	m_swordSprite->SetY(m_swordBody->GetPosition().y);
	if (m_isAttacking)
	{
		m_swordSprite->Process(deltaTime);
	}
}

void 
Sword::SetAttacking(bool isAttacking)
{
	//std::string position1 = "before sword position x : " + std::to_string(m_swordBody->GetPosition().x) + ", y: " + std::to_string(m_swordBody->GetPosition().y);
	//SDL_Log(position1.c_str());
	m_isAttacking = isAttacking;
	m_swordBody->GetFixtureList()->SetSensor(!isAttacking);
	//m_swordBody->SetTransform(b2Vec2(m_player.GetPositionX() + 22.0f, m_player.GetPositionY() - 6.0f), 0.0);
	//std::string position2 = "after sword position x : " + std::to_string(m_swordBody->GetPosition().x) + ", y: " + std::to_string(m_swordBody->GetPosition().y);
	//SDL_Log(position2.c_str());
}

void
Sword::StartContact()
{
	SDL_Log("Sword made contact");
}

bool
Sword::IsAttacking()
{
	return m_isAttacking;
}

void 
Sword::ChangeSwordDirection(Direction direction, b2World& world)
{
	
	if (!m_isAttacking || direction == swordDirection)
	{
		SDL_Log("not attacking");
		return;
	}
	else
	{
		SDL_Log("attacking!");
	}
	//sword triange collision polygon
	b2Vec2 vertices[3];
	int32 count = 3;
	//origin point of the sword, should be the left and/or top most edge of the designated edge
	float positionX;
	float positionY;
	switch (direction)
	{
	case Direction::UP:
		positionX = m_player.GetPositionX();
		positionY = m_player.GetPositionY();
		vertices[0].Set(28.0f, 0);
		vertices[1].Set(56.0f, -48.0f);
		vertices[2].Set(0.0f, -48.0f);
		break;
	case Direction::DOWN:
		positionX = m_player.GetPositionX();
		positionY = m_player.GetPositionY() + 64.0f;
		vertices[0].Set(28.0f, 0);
		vertices[1].Set(56.0f, 48.0f);
		vertices[2].Set(0.0f, 48.0f);
		break;
	case Direction::LEFT:
		positionX = m_player.GetPositionX();
		positionY = m_player.GetPositionY();
		vertices[0].Set(28.0f, 0);
		vertices[1].Set(56.0f, -48.0f);
		vertices[2].Set(0.0f, -48.0f);
		break;
	case Direction::RIGHT:
		positionX = m_player.GetPositionX() + 64.0f;
		positionY = m_player.GetPositionY();
		vertices[0].Set(28.0f, 0);
		vertices[1].Set(56.0f, -48.0f);
		vertices[2].Set(0.0f, -48.0f);
		break;
	}
	SetupSwordCollisionPolygon(positionX, positionY, vertices, count, world);
	swordDirection = direction;
}