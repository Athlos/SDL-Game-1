// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <cmath>

Entity::Entity()
	: m_pSprite(0)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_velocityX(0.0f)
	, m_velocityY(0.0f)
	, m_dead(false)
{
	m_classType = ClassType::BLANK;
}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite, b2World& m_world)
{
	m_x = 300;
	m_y = 300;
	assert(sprite);
	m_pSprite = sprite;
	SetupCollision(m_world);
	return (true);
}

void
Entity::Process(float deltaTime)
{
	m_x = m_entityBody->GetPosition().x;
	m_y = m_entityBody->GetPosition().y;
	m_pSprite->SetX(static_cast<int>(m_x) - 16.0f);
	m_pSprite->SetY(static_cast<int>(m_y) - 16.0f);
}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
	backBuffer.DebugDrawCollision(*m_entityBody, m_entityShape);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	float x1 = e.GetPositionX();
	float y1 = e.GetPositionY();
	float radius1 = 16;
	float radius2 = 16;
	if (sqrt(pow((x1 - m_x), 2) + pow((y1 - m_y), 2)) < (radius1 + radius2))
	{
		return true;
	}
	return false;
}

void
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

float
Entity::GetPositionX()
{
	return (m_x);
}

float
Entity::GetPositionY()
{
	return (m_y);
}

float
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

void 
Entity::SetPosition(int x, int y)
{
	m_entityBody->SetTransform(b2Vec2(x, y), 0);
	m_pSprite->SetX(static_cast<int>(m_entityBody->GetPosition().x));
	m_pSprite->SetY(static_cast<int>(m_entityBody->GetPosition().y));
}

bool
Entity::IsDead()
{
	return (m_dead);
}

void
Entity::SetupCollision(b2World& m_world)
{
	m_entityBodyDef.type = b2_dynamicBody;
	m_entityBodyDef.position.Set(static_cast<float>(m_x), static_cast<float>(m_y));
	m_entityBodyDef.angle = 0;
	m_entityBody = m_world.CreateBody(&m_entityBodyDef);
	m_entityShape.SetAsBox(16, 16);
	m_entityFixtureDef.shape = &m_entityShape;
	m_entityFixtureDef.density = 1;
	m_entityBody->CreateFixture(&m_entityFixtureDef);
	m_entityBody->SetUserData(this);
}

void
Entity::StartContact()
{
	SDL_Log("Some Collision Happened");
}

b2Body*
Entity::GetEntityBody()
{
	return m_entityBody;
}

void
Entity::SetEntityCollisionVelocity(b2Vec2 collisionVelocity)
{
	m_entityBody->SetLinearVelocity(collisionVelocity);
}

void
Entity::SetEntityDensity(float mass)
{
	m_entityFixtureDef.density = mass;
}

void
Entity::InverseVelocity()
{
	b2Vec2 currentVelocity = m_entityBody->GetLinearVelocity();
	SetEntityCollisionVelocity(b2Vec2(currentVelocity.x*-1, currentVelocity.y*-1));
}

void
Entity::RotateEntity(float angleDegree)
{
	m_entityBody->SetTransform(m_entityBody->GetPosition(), M_PI/180.0f * angleDegree);
}