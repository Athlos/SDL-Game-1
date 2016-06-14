#pragma once

#include "entity.h"

#include <vector>

class Player;

enum EnemyState
{
	ATTACKING,
	CHARGING,
	PATROLLING,
	IDLING
};

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	//Core functions
	bool Initialise(AnimatedSprite* p_animSprite, b2World& m_world);
	void Process(float deltaTime, Player* player);
	void Draw(BackBuffer& backbuffer);
	void SetPosition(float x, float y);
	void SetEnemyState(EnemyState state);

	//Health functions
	int GetCurrentHealth();
	void SetCurrentHealth(int CurrentHealth);

	int GetMaxHealth();
	void SetMaxHealth(int MaxHealth);

	void UpdateEnemyHealth(int Damage);
	bool IsDead();

	//Combat
	void ApproachPlayer();
	void AttackPlayer(Player* player);
	bool IsInRange(int x, int y, int range);
	
	//Drop loot
	void GetReward();

	//Movement and waypoints
	void AddWaypoint(int x, int y);
	void MoveTo(int x, int y, float deltaTime);
	void UpdateWaypoints();

	void SavePatrolToDisk(const char* pcFilename);
	bool LoadPatrolFromDisk(const char* pcFilename);
	void ClearWaypoints();

	//Debug 
	void DrawWaypoints(BackBuffer& backbuffer);

	//Member Data:
public:

protected:

private:
	AnimatedSprite* m_pSprite;

	EnemyState m_enemyState;

	//Health 
	int m_maxHealth;
	int m_currentHealth;

	//Detection and attack
	int m_attackRange;
	int m_detectRange;

	//Enemy movement
	float m_speed;
	std::vector<SDL_Point*> m_waypoints;
	SDL_Point* m_currentWaypoint;
	int m_currentWaypointIndex;
	bool m_loopPatrol;

	//Enemy attack
	int m_attackDamage;
	float m_attackSpeed;
	float m_attackSpeedTimer;
};

