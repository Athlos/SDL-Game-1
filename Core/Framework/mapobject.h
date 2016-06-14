#ifndef __MAPOBJECT_H__
#define __MAPOBJECT_H__

#include "sprite.h"
#include "Box2D.h"
#include "direction.h"

enum ObjectType
{
	COLLIDABLE,
	BREAKABLE,
	EMPTY
};

class MapObject
{
	//Member Functions
public:
	MapObject();
	~MapObject();
	bool Initialise(BackBuffer &backBuffer, char TileRepresentation);
	void SetupCollision(b2World& m_world);
	void Draw(BackBuffer &backBuffer);
	void Process(float deltaTime);
	
	//getters
	bool GetIfCollidable();
	bool GetIfBreakable();
	Sprite* GetSprite();
	char GetTileReprensentation();
	int GetPositionX();
	int GetPositionY();
	b2BodyDef GetObjectBodyDef();
	//setters
	void SetIfCollidable(bool isCollidable);
	void SetIfBreakable(bool isBreakable);
	void SetPositionX(int x);
	void SetPositionY(int y);
	void StartContact();
	void EndContact();
	bool GetIfDestroyed();
	b2Body* GetObjectBody();
protected:
private:
	//Member Data
public:
	ClassType type;
protected:
private:
	int m_x;
	int m_y;
	bool m_isCollidable;
	bool m_isBreakable;
	Sprite* m_objectSprite;
	char m_tileRepresentation;

	b2BodyDef m_objectBodyDef;
	b2Body* m_objectBody;
	b2PolygonShape m_objectShape;
	b2FixtureDef m_objectFixtureDef;

	bool m_isColliding;
	bool m_isDestroyed;

	
};
#endif // !__MAPOBJECT_H__
