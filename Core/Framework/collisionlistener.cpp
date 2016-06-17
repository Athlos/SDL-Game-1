#include "collisionlistener.h"
#include "player.h"
#include "mapobject.h"
#include "sword.h"
#include "direction.h"

#include <typeinfo>


void
CollisionListener::BeginContact(b2Contact* contact)
{
	void* contactA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* contactB = contact->GetFixtureB()->GetBody()->GetUserData();

	ClassType typeA = static_cast<MapObject*>(contactA)->type;
	ClassType typeB = static_cast<Sword*>(contactB)->type;
	bool isAttacking = static_cast<Sword*>(contactB)->IsAttacking();

	if (typeA == ClassType::MAPOBJECT && typeB == ClassType::SWORD && isAttacking)
	{
		static_cast<MapObject*>(contactA)->StartContact();
	}
	/*
	void* userData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (userData)
	{
		//static_cast<Sword*>(userData)->StartContact();

		bool isAttacking = static_cast<Sword*>(userData)->IsAttacking();


		if (isAttacking)
		{
			userData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (userData)
			{
				char objType = static_cast<MapObject*>(userData)->GetTileReprensentation();

				//check if the object is a breakable object
				if (objType == 'B')
				{//if these are true set the object's bool to colliding to equal false
					static_cast<MapObject*>(userData)->StartContact();
				}
			}
		}
	}*/
	/*
	void* userData = contact->GetFixtureA()->GetBody()->GetUserData();
	//Check if Contact A is a player
	if (userData)
	{//if it is a player
		//set the player's bool to colliding to equal true
		static_cast<Player*>(userData)->StartContact();
		static_cast<Sword*>(userData)->StartContact();
	}

	userData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (userData)
	{//Check if Contact B is an object
		char objType = static_cast<MapObject*>(userData)->GetTileReprensentation();
		//check if the object is a breakable object
		if (objType == 'B')
		{//if these are true set the object's bool to colliding to equal false
			static_cast<MapObject*>(userData)->StartContact();
		}
	}*/
}

void
CollisionListener::EndContact(b2Contact* contact)
{
	/*
	void* userData = contact->GetFixtureA()->GetBody()->GetUserData();
	//Check if Contact A is the player
	if (userData)
	{//set the player's bool to colliding to equal true
		static_cast<Player*>(userData)->EndContact();
	}

	userData = contact->GetFixtureB()->GetBody()->GetUserData();
	//Check if Contact B is an object
	if (userData)
	{//set the object's bool to colldiing equal to false
		static_cast<MapObject*>(userData)->EndContact();
	}	
	*/
}