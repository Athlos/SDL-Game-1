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

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite, b2World& m_world)
{
	assert(sprite);
	m_pSprite = sprite;
	SetupCollision(m_world);
	return (true);
}

void
Entity::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_x += deltaTime * (m_velocityX);
	m_y += deltaTime * (m_velocityY);

}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
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
	m_x = x;
	m_y = y;
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
}

bool
Entity::IsDead()
{
	return (m_dead);
}

void
Entity::SetupCollision(b2World& m_world)
{
	m_entityBodyDef.type = b2_staticBody;
	m_entityBodyDef.position.Set(static_cast<float>(m_x), static_cast<float>(m_y));
	m_entityBodyDef.angle = 0;
	m_entityBody = m_world.CreateBody(&m_entityBodyDef);
	m_entityShape.SetAsBox(1 * PIXELSTOMETRES, 1 * PIXELSTOMETRES);
	m_entityFixtureDef.shape = &m_entityShape;
	m_entityFixtureDef.density = 1;
	m_entityBody->CreateFixture(&m_entityFixtureDef);
}