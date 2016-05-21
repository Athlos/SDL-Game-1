#ifndef __PLAYER_H__
#define __PLAYER_H__

//Class declarations
#include "entity.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "direction.h"
#include "pickup.h"

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
	void UpdatePlayerDirection(Direction dir);

	bool CheckPickup(Pickup& pickup);

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

	//Pickup range
	int m_pickupRangeX;
	int m_pickupRangeY;

	//Testing the box2d Rectangle body, will be removed later
	b2BodyDef m_testBodyDef;
};

#endif //__PLAYER_H__
