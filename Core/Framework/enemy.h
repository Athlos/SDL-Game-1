#pragma once

#include "entity.h"


class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	//Core functions
	bool Initialise(AnimatedSprite* p_animSprite, b2World& m_world);
	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void SetPosition(float x, float y);

	//Health functions
	int GetCurrentHealth();
	void SetCurrentHealth(int CurrentHealth);

	int GetMaxHealth();
	void SetMaxHealth(int MaxHealth);

	bool IsDead();
	
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
};

