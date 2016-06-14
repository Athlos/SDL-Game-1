#include "enemy.h"
#include "animatedsprite.h"
#include "player.h"


Enemy::Enemy()
{
	//Loading base stats of enemies
	m_speed = 20;
	m_attackDamage = 1;
	m_attackSpeed = 1.5;
	m_attackSpeedTimer = 0;
	m_attackRange = 50;
	m_detectRange = 300;
	m_enemyState = IDLING;
	m_currentWaypointIndex = 0;
	m_currentWaypoint = 0;
	m_loopPatrol = true;
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

	//Check if within sight range of player
	if (IsInRange(player->GetPositionX(), player->GetPositionY(), m_detectRange))
	{
		//Set state to charging
		SetEnemyState(CHARGING);

		//Charge towards player in a straight line
		MoveTo(player->GetPositionX(), player->GetPositionY(), deltaTime);

		//Check if player is within attack range and can attack
		if (IsInRange(player->GetPositionX(), player->GetPositionY(), m_attackRange)  && m_attackSpeed <= m_attackSpeedTimer)
		{
			//Set state to attacking
			SetEnemyState(ATTACKING);

			AttackPlayer(player);
			m_attackSpeedTimer = 0;
		}
	}
	else          //If player is not visible, follow the waypoints on the path
	{
		//Check if waypoints are set
		if (!m_waypoints.empty())
		{
			//Set enemy to patrolling
			SetEnemyState(PATROLLING);
			//Move to current waypoint
			MoveTo(m_currentWaypoint->x, m_currentWaypoint->y, deltaTime);
			UpdateWaypoints();
		}
		else
		{
			//Set enemy to idle
			SetEnemyState(IDLING);
		}
	}
	

	m_pSprite->SetX(m_x);
	m_pSprite->SetY(m_y);
	if (m_enemyState != IDLING)
	{
		m_pSprite->Process(deltaTime);
	}
	
	//TODO - sort out box2d positions
	//m_x = m_playerBody->GetPosition().x;
	//m_y = m_playerBody->GetPosition().y;
	//m_animSprite->SetX(static_cast<int>(m_playerBody->GetPosition().x));
	//m_animSprite->SetY(static_cast<int>(m_playerBody->GetPosition().y));
	//m_animSprite->Process(deltaTime);
}

void 
Enemy::DrawWaypoints(BackBuffer& backbuffer)
{
	if (m_currentWaypoint != 0)
	{
		backbuffer.SetDrawColour(255, 255, 255, 0);
		backbuffer.DrawLine(m_x, m_y, m_currentWaypoint->x, m_currentWaypoint->y);
	}

	backbuffer.SetDrawColour(255, 0, 0, 0);

	for (int i = 0; i < m_waypoints.size(); i++)
	{
		SDL_Point* sp = m_waypoints.at(i);
		//draw line from enemy
		if (i == 0) 
		{
			//backbuffer.DrawLine(m_x, m_y, m_curr->x, sp->y);
		}
		else
		{
			SDL_Point* previous = m_waypoints.at(i-1);
			backbuffer.DrawLine(sp->x, sp->y, previous->x, previous->y);
		}
	}
	//draw loop
	if (m_loopPatrol && !m_waypoints.empty())
	{
		backbuffer.SetDrawColour(0, 255, 0, 0);
		backbuffer.DrawLine(m_waypoints.at(0)->x, m_waypoints.at(0)->y, m_waypoints.at(m_waypoints.size()-1)->x, m_waypoints.at(m_waypoints.size()-1)->y);
	}

}

void
Enemy::MoveTo(int x, int y, float deltaTime)
{
	//Move to coordinates
	float angle = atan2((m_x + 64) - x, (m_y + 64) - y);
	angle *= 180 / M_PI;
	angle *= -1;
	m_pSprite->SetAngle(angle);
	float dirX = x - m_x;
	float dirY = y - m_y;
	float hyp = sqrt(dirX*dirX + dirY*dirY);
	dirX /= hyp;
	dirY /= hyp;
	
	if (m_enemyState == CHARGING) {
		m_x += deltaTime * dirX * (m_speed*1.5);
		m_y += deltaTime * dirY * (m_speed*1.5);
	}
	else
	{
		m_x += deltaTime * dirX * m_speed;
		m_y += deltaTime * dirY * m_speed;
	}
}

void
Enemy::SetEnemyState(EnemyState state)
{
	m_enemyState = state;
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
	backBuffer.DrawRectangle(m_x, m_y - 5, m_x + (64 * (static_cast<float>(m_currentHealth) / static_cast<float>(m_maxHealth))), m_y);
}

//Health functions
int
Enemy::GetCurrentHealth()
{
	return m_currentHealth;
}

int
Enemy::GetMaxHealth()
{
	return m_maxHealth;
}

void
Enemy::SetCurrentHealth(int CurrentHealth)
{
	m_currentHealth = CurrentHealth;
}

void
Enemy::SetMaxHealth(int MaxHealth)
{
	m_maxHealth = MaxHealth;
}

bool
Enemy::IsDead()
{
	return (m_currentHealth <= 0);
}

void
Enemy::UpdateEnemyHealth(int HealthChange)
{
	m_currentHealth += HealthChange;

	if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
	}
	if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}

void
Enemy::AttackPlayer(Player* player)
{
	player->UpdatePlayerHealth(-m_attackDamage);
}

bool
Enemy::IsInRange(int x, int y, int range)
{
	//Check if location is in range
	int xDifference = m_x - x;
	int yDifference = m_y - y;

	if (xDifference < 0) {
		xDifference *= -1;
	}

	if (yDifference < 0) {
		yDifference *= -1;
	}

	if (xDifference < range && yDifference < range)
	{
		return true;
	}
	return false;
}

void
Enemy::AddWaypoint(int x, int y)
{
	SDL_Point* newPoint = new SDL_Point{x, y};
	if (m_currentWaypoint == 0)
	{
		m_currentWaypoint = newPoint;
	}
	m_waypoints.push_back(newPoint);
}

void
Enemy::UpdateWaypoints()
{
	//make sure waypoints exist
	if (m_currentWaypoint == 0 || m_waypoints.empty())
	{
		return;
	}

	//Check if enemy is close enough to current waypoint to move to next one
	if (IsInRange(m_currentWaypoint->x, m_currentWaypoint->y, 10))
	{
		//Waypoint is reached, update to new waypoint, or idle if no new wayponts
		if (m_currentWaypointIndex < m_waypoints.size() - 1)
		{
			//Set new waypoint
			m_currentWaypointIndex++;
			m_currentWaypoint = m_waypoints.at(m_currentWaypointIndex);
		}
		else
		{
			if (m_loopPatrol && !m_waypoints.empty())
			{
				m_currentWaypointIndex = 0;
				m_currentWaypoint = m_waypoints.at(0);
			}
			//No new waypoints, and patrol path does not circle
			//Start idling
			SetEnemyState(IDLING);
			//m_currentWaypoint = 0;
		}
	}


}