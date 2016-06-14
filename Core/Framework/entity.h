// 717310 C++ SDL Framework
#ifndef __ENTITY_H__
#define __ENTITY_H__


// Forward Declarations:
#include "backbuffer.h"
#include "sprite.h"
#include "conversion.h"
#include "Box2D.h"

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite, b2World& m_world);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead();

	bool IsCollidingWith(Entity& e);

	float GetPositionX();
	float GetPositionY();

	float GetHorizontalVelocity();
	void SetHorizontalVelocity(float x);

	float GetVerticalVelocity();
	void SetVerticalVelocity(float y);

	void SetPosition(int x, int y);
	void SetupCollision(b2World& m_world, float boxSize);
	
protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

	//Entity Box2D Variables
	b2BodyDef m_entityBodyDef;
	b2Body* m_entityBody;
	b2PolygonShape m_entityShape;
	b2FixtureDef m_entityFixtureDef;


	
private:

};

#endif //__ENTITY_H__
