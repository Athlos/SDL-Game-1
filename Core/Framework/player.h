#ifndef __PLAYER_H__
#define __PLAYER_H__

//Class declarations
#include "entity.h"
#include "animatedsprite.h"
#include "backbuffer.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	bool Initialise(AnimatedSprite* p_animSprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void SetPositionX(float x);
	void SetPositionY(float y);

	int GetCurrentHealth();
	void SetCurrentHealth(int CurrentHealth);

	int GetMaxHealth();
	void SetMaxHealth(int MaxHealth);

	void UpdatePlayerHealth(int Damage);


protected:
private:

	//Variables
public:
protected:
private:
	AnimatedSprite* m_animSprite;
	int m_x;
	int m_y;

	//Health 
	int m_MaxHealth;
	int m_CurrentHealth;

};

#endif //__PLAYER_H__
