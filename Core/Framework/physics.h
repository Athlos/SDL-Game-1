#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <box2d.h>
#include "Common\b2math.h"
#include "Dynamics\b2World.h"

class b2World;
struct b2Vec2;

class Physics
{
	//Member Methods
public:
	Physics(b2Vec2 gravity);
protected:
private:
	//Member Data
public:
protected:
private:
	//b2Vec2 m_gravity;
	//b2World m_world;
};

#endif // __PHYSICS_H__

