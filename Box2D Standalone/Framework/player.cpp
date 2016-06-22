#include "player.h"

#include "sprite.h"
#include "backbuffer.h"
#include <cassert>

Player::Player()
: m_animSprite(0)
, m_isColliding(false)
{
	Entity::Entity();
	m_x = 400;
	m_y = 560;

	//Pickup range defaults
	m_pickupRangeX = 50;
	m_pickupRangeY = 50;
}

Player::~Player()
{
}

bool
Player::Initialise(AnimatedSprite* p_animSprite, b2World& m_world)
{
	//Set up player sprite
	assert(p_animSprite);
	m_animSprite = p_animSprite;
	m_animSprite->SetY(static_cast<int>(m_y));
	m_animSprite->SetX(static_cast<int>(m_x));
	//setup for player collision
	SetupCollision(m_world);
	return (true);
}

void Player::Process(float deltaTime)
{
	m_x = m_playerBody->GetPosition().x;
	m_y = m_playerBody->GetPosition().y;
	m_animSprite->SetX(static_cast<int>(m_x) - 32.0f);
	m_animSprite->SetY(static_cast<int>(m_y) - 32.0f);
	m_animSprite->Process(deltaTime);
}

void Player::Draw(BackBuffer& backBuffer)
{
	assert(m_animSprite);
	m_animSprite->Draw(backBuffer);
	backBuffer.DebugDrawCollision(*m_playerBody, m_playerShape);
}

void
Player::SetPositionX(float x)
{
	m_x = (static_cast<int>(x));
	m_animSprite->SetX(static_cast<int>(m_x));
}
void
Player::SetPositionY(float y)
{
	m_y = (static_cast<int>(y));
	m_animSprite->SetY(static_cast<int>(m_y));
}

float
Player::GetPositionX()
{
	return m_x;
}

float
Player::GetPositionY()
{
	return m_y;
}

int Player::GetCurrentHealth()
{
	return m_CurrentHealth;
}

int Player::GetMaxHealth()
{
	return m_MaxHealth;
}

void Player::SetCurrentHealth(int CurrentHealth)
{
	m_CurrentHealth = CurrentHealth;
}

void Player::SetMaxHealth(int MaxHealth)
{
	m_MaxHealth = MaxHealth;
}

/* Updates the players health by adding to it the amount specified
*@param HealthChange the amount to be added to health, make negative if it is damage
*/
void Player::UpdatePlayerHealth(int HealthChange)
{
	m_CurrentHealth += HealthChange;

	if (m_CurrentHealth < 0)
	{
		m_CurrentHealth = 0;
	}
	if (m_CurrentHealth > m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}
}

void Player::UpdatePlayerDirection(Direction dir)
{
	m_animSprite->UpdateDirection(dir);
}


void
Player::SetupCollision(b2World& m_world)
{
	m_playerBodyDef.type = b2_dynamicBody;
	m_playerBodyDef.position.Set(static_cast<float>(m_x), static_cast<float>(m_y));
	m_playerBodyDef.angle = 0;
	m_playerBody = m_world.CreateBody(&m_playerBodyDef);
	m_playerShape.SetAsBox(32, 32);
	m_playerFixtureDef.shape = &m_playerShape;
	m_playerFixtureDef.density = 30.0f;
	m_playerBody->CreateFixture(&m_playerFixtureDef);
	m_playerBody->SetUserData(this);
}

void
Player::SetPosition(float x, float y)
{
	m_playerBody->SetTransform(b2Vec2(x, y), 0);
	m_animSprite->SetX(static_cast<int>(m_playerBody->GetPosition().x));
	m_animSprite->SetY(static_cast<int>(m_playerBody->GetPosition().y));
}

void
Player::SetPlayerCollisionVelocity(b2Vec2 collisionVelocity)
{
	m_playerBody->SetLinearVelocity(collisionVelocity);
}
b2Body*
Player::GetPlayerBody()
{
	return m_playerBody;
}

void
Player::StartContact()
{
	m_isColliding = true;
}
void
Player::EndContact()
{
	m_isColliding = false;
}