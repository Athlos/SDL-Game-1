#include "collisionlistener.h"
#include "player.h"
#include "mapobject.h"

void
CollisionListener::BeginContact(b2Contact* contact)
{
	void* userData = contact->GetFixtureA()->GetBody()->GetUserData();
	//Check if Contact A is a player
	if (userData)
	{//if it is a player
		//set the player's bool to colliding to equal true
		static_cast<Player*>(userData)->StartContact();
	}

	userData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (userData)
	{//Check if Contact B is an object
		char objType = static_cast<MapObject*>(userData)->GetTileReprensentation();
		//check if the object is a breakable object
		if (objType == 'B')
		{//if these are true set the object's bool to colliding to equal false
			static_cast<MapObject*>(userData)->SetIfCollidable(true);
		}
	}
}

void
CollisionListener::EndContact(b2Contact* contact)
{
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
		//static_cast<MapObject*>(userData)->EndContact();
	}	
}