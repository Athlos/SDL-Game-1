#pragma once

#include "entity.h"

class Player;


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
	
	//Drop loot
	void GetReward();

	//Member Data:
public:

protected:

private:
	AnimatedSprite* m_pSprite;

	//Health 
	int m_MaxHealth;
	int m_CurrentHealth;

	//Enemy movement speed
	float m_speed;

	//Enemy attack cooldown
	float m_attackSpeed;
	float m_attackSpeedTimer;
};

