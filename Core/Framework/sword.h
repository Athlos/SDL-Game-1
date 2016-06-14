#ifndef __SWORD_H__
#define __SWORD_H__

#include "Box2D.h"
#include "entity.h"
#include "animatedsprite.h"
#include "Box2D.h"
#include "player.h"
#include "direction.h"

class Sword
{
//members
public:
	Sword(Player& player);
	~Sword();
	void Initialise(AnimatedSprite* swordSprite, b2World& world);
	void SetupCollision(b2World& world);
	void Draw(BackBuffer& backBuffer);
	void Process(float deltaTime);
	void SetAttacking(bool isAttacking);
	void StartContact();
	bool IsAttacking();
	void ChangeSwordDirection(Direction direction, b2World& world);
	//needed to change direction of the sword's sprite and collision polygon based on the direction the player is facing
	//currently takes in position x and y (which are modified to where the midpoint of each edge is) an array of vertices (3 for now) that make up the polygon
	//of the collision box and the count which is just the amount of points in the vertices, the world object is also needed to recreate the welded joint between
	//the sword and player
	void SetupSwordCollisionPolygon(float positionX, float positionY, b2Vec2 vertices[3], int32 count, b2World& world);

protected:
private:
//variables
public:
	ClassType type;
protected:
private:
	AnimatedSprite* m_swordSprite;
	bool m_isAttacking;
	Player& m_player;
	float m_x;
	float m_y;
	
	//Sword Box2D Variables
	b2BodyDef m_swordBodyDef;
	b2Body* m_swordBody;
	b2PolygonShape m_swordShape;
	b2FixtureDef m_swordFixtureDef;

	b2WeldJointDef swordWeldToPlayer;

	Direction swordDirection;

	
};

#endif // !__SWORD_H__
