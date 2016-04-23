#include "player.h"

#include "sprite.h"
#include "backbuffer.h"
#include <cassert>

Player::Player()
: m_animSprite(0)
{
	Entity::Entity();
	m_x = 400;
	m_y = 560;
}

Player::~Player()
{
}

bool
Player::Initialise(AnimatedSprite* p_animSprite)
{
	//Set up player sprite
	assert(p_animSprite);
	m_animSprite = p_animSprite;
	m_animSprite->SetY(static_cast<int>(m_y));
	m_animSprite->SetX(static_cast<int>(m_x));

	return (true);
}

void Player::Process(float deltaTime)
{
	m_animSprite->SetX(static_cast<int>(m_x));
	m_animSprite->SetY(static_cast<int>(m_y));

	m_x += (static_cast<int>(deltaTime * m_velocityX));
	m_y += (static_cast<int>(deltaTime * m_velocityY));
	m_animSprite->SetFrameSpeed(0.08f);
	m_animSprite->Process(deltaTime);
}

void Player::Draw(BackBuffer& backBuffer)
{
	assert(m_animSprite);
	m_animSprite->Draw(backBuffer);
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