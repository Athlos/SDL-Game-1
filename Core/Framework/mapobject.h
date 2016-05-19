#ifndef __MAPOBJECT_H__
#define __MAPOBJECT_H__

#include "sprite.h"

enum ObjectType
{
	COLLIDABLE,
	BREAKABLE,
	EMPTY
};

class MapObject : public Sprite
{
	//Member Functions
public:
	MapObject();
	~MapObject();
	bool Initialise(BackBuffer &backBuffer, char TileRepresentation);
	void Draw(BackBuffer &backBuffer);
	void Process(float deltaTime);
	//getters
	bool GetIfCollidable();
	bool GetIfBreakable();
	//setters
	void SetIfCollidable(bool isCollidable);
	void SetIfBreakable(bool isBreakable);
protected:
private:
	//Member Data
public:
protected:
private:
	bool m_isCollidable;
	bool m_isBreakable;
	Sprite* m_ObjectSprite;
	char m_tileRepresentation;
};
#endif // !__MAPOBJECT_H__
