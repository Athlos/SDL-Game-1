#include "enemy.h"
#include "animatedsprite.h"
#include "player.h"


Enemy::Enemy()
{
	m_speed = 50;
	m_attackSpeed = 1.5;
	m_attackSpeedTimer = 0;
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
Enemy::Process(float deltaTime, Player* player)
{
	//Refresh attacks
	m_attackSpeedTimer += deltaTime;
	//Enemies move towards player

	//Check if within sight range of player
	int xDifference = m_x - player->GetPositionX();
	int yDifference = m_y - player->GetPositionY();

	if (xDifference < 0) {
		xDifference *= -1;
	}

	if (yDifference < 0) {
		yDifference *= -1;
	}

	if (xDifference < 400 && yDifference < 400)
	{
		float angle = atan2((m_x + 64) - player->GetPositionX(), (m_y + 64) - player->GetPositionY());
		angle *= 180 / M_PI;
		angle *= -1;
		m_pSprite->SetAngle(angle);
		float dirX = player->GetPositionX() - m_x;
		float dirY = player->GetPositionY() - m_y;
		float hyp = sqrt(dirX*dirX + dirY*dirY);
		dirX /= hyp;
		dirY /= hyp;
		m_x += deltaTime * dirX * m_speed;
		m_y += deltaTime * dirY * m_speed;
	}
	//If close enough, attack player
	if (xDifference < 50 && yDifference < 50 && m_attackSpeed <= m_attackSpeedTimer)
	{
		AttackPlayer(player);
		m_attackSpeedTimer = 0;
	}

	m_pSprite->SetX(m_x);
	m_pSprite->SetY(m_y);
	m_pSprite->Process(deltaTime);
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
	backBuffer.SetDrawColour(255, 255, 255);
	backBuffer.DrawRectangleUnfilled(m_x, m_y, m_x + 64, m_y + 64);
	backBuffer.SetDrawColour(0, 0, 0);
	backBuffer.DrawRectangleUnfilled(m_x, m_y - 5, m_x + 64, m_y);
	backBuffer.SetDrawColour(255, 0, 0);
	backBuffer.DrawRectangle(m_x, m_y - 5, m_x + (64 * (static_cast<float>(m_CurrentHealth) / static_cast<float>(m_MaxHealth))), m_y);
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

void
Enemy::UpdateEnemyHealth(int HealthChange)
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

void
Enemy::AttackPlayer(Player* player)
{
	player->UpdatePlayerHealth(-1);
}