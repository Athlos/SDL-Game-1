#ifndef __PLAYER_H__
#define __PLAYER_H__

//Class declarations
#include "entity.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "direction.h"
#include "pickup.h"
#include "Box2D.h"
#include "conversion.h"
#include "gamemap.h"
#include "mapobject.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	bool Initialise(AnimatedSprite* p_animSprite, b2World& m_world);
	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void SetPositionX(float x);
	void SetPositionY(float y);
	float GetPositionX();
	float GetPositionY();

	int GetCurrentHealth();
	void SetCurrentHealth(int CurrentHealth);

	int GetMaxHealth();
	void SetMaxHealth(int MaxHealth);

	void UpdatePlayerHealth(int Damage);
	void UpdatePlayerDirection(Direction dir);

	bool CheckPickup(Pickup& pickup);

	void SetupCollision(b2World& m_world);
	void SetPlayerCollisionVelocity(b2Vec2 collisionVelocity);
	b2Body* GetPlayerBody();
	void StartContact();
	void EndContact();
protected:
private:

	//Variables
public:
protected:
private:
	AnimatedSprite* m_animSprite;

	//Health 
	int m_MaxHealth;
	int m_CurrentHealth;

	//Pickup range
	int m_pickupRangeX;
	int m_pickupRangeY;

	//Player Box2D Variables
	b2BodyDef m_playerBodyDef;
	b2Body* m_playerBody;
	b2PolygonShape m_playerShape;
	b2FixtureDef m_playerFixtureDef;

	bool m_isColliding;
};

#endif //__PLAYER_H__
