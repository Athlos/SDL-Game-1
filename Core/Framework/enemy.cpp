#include "enemy.h"
#include "animatedsprite.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

//Core Functions
bool
Enemy::Initialise(AnimatedSprite* p_animSprite, b2World& m_world)
{
	//Set up enemy sprite
	assert(p_animSprite);
	m_pSprite = p_animSprite;
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->SetX(static_cast<int>(m_x));
	//setup for player collision
	SetupCollision(m_world);
	return (true);
}

void
Enemy::Process(float deltaTime)
{
	//TODO - sort out box2d positions
	//m_x = m_playerBody->GetPosition().x;
	//m_y = m_playerBody->GetPosition().y;
	//m_animSprite->SetX(static_cast<int>(m_playerBody->GetPosition().x));
	//m_animSprite->SetY(static_cast<int>(m_playerBody->GetPosition().y));
	//m_animSprite->Process(deltaTime);
}

void
Enemy::SetPosition(float x, float y)
{
	m_x = (static_cast<int>(x));
	m_pSprite->SetX(static_cast<int>(m_x));
	m_y = (static_cast<int>(y));
	m_pSprite->SetY(static_cast<int>(m_y));
}

void
Enemy::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
	//Debug collision bounds
	backBuffer.DrawRectangleUnfilled(m_x, m_y, m_x + 64, m_y + 64);
}

//Health functions
int
Enemy::GetCurrentHealth()
{
	return m_CurrentHealth;
}

int
Enemy::GetMaxHealth()
{
	return m_MaxHealth;
}

void
Enemy::SetCurrentHealth(int CurrentHealth)
{
	m_CurrentHealth = CurrentHealth;
}

void
Enemy::SetMaxHealth(int MaxHealth)
{
	m_MaxHealth = MaxHealth;
}

bool
Enemy::IsDead()
{
	return (m_CurrentHealth <= 0);
}