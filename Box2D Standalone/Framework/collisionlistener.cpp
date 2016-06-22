#include "collisionlistener.h"
#include "player.h"
#include "mapobject.h"
#include "direction.h"


void
CollisionListener::BeginContact(b2Contact* contact)
{
	//Get the user data of the collided objects
	void* contactA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* contactB = contact->GetFixtureB()->GetBody()->GetUserData();
	//Save their class type
	ClassType typeA = static_cast<Entity*>(contactA)->m_classType;
	ClassType typeB = static_cast<Entity*>(contactB)->m_classType;
	//if the player or paddle collides with the ball
	if (typeB == ClassType::BALL && (typeA == ClassType::PADDLE || typeA == ClassType::PLAYER))
	{//inverse the velocity
		static_cast<Entity*>(contactB)->InverseVelocity();
	}
}

void
CollisionListener::EndContact(b2Contact* contact)
{

}