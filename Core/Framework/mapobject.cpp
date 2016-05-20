#include "mapobject.h"
#include "backbuffer.h"
#include <cassert>

MapObject::MapObject()
:m_isCollidable(false)
, m_isBreakable(false)
, m_tileRepresentation('E')
{
}

MapObject::~MapObject() 
{
}

bool
MapObject::Initialise(BackBuffer & backBuffer, char TileRepresentation)
{
	switch (TileRepresentation)
	{
	case 'C':
		m_ObjectSprite = backBuffer.CreateSprite("Assets\\rock.png");
		m_isCollidable = true;
		m_isBreakable = false;
		m_tileRepresentation = TileRepresentation;
		return true;
	case 'B':
		m_ObjectSprite = backBuffer.CreateSprite("Assets\\pot.png");
		m_isCollidable = false;
		m_isBreakable = true;
		m_tileRepresentation = TileRepresentation;
		return true;
	case 'E':
		m_isCollidable = false;
		m_isBreakable = false;
		m_tileRepresentation = TileRepresentation;
		return true;
	default:
		return false;
	}
}

void
MapObject::Draw(BackBuffer &backBuffer)
{//if the tile is not equal to an empty tile
	if (m_tileRepresentation != 'E')
	{//draw
		assert(m_ObjectSprite);
		m_ObjectSprite->Draw(backBuffer);
	}//otherwise don't
}

void
MapObject::Process(float deltaTime)
{
	//if object is breakable, and the player hits the object break the object
	//spawn coins/hearts and delete object from map.
}

bool 
MapObject::GetIfCollidable() 
{
	return (m_isCollidable);
}

bool 
MapObject::GetIfBreakable() 
{
	return (m_isBreakable);
}

void 
MapObject::SetIfCollidable(bool isCollidable) 
{
	m_isCollidable = isCollidable;
}

void 
MapObject::SetIfBreakable(bool isBreakable) 
{
	m_isBreakable = isBreakable;
}

Sprite*
MapObject::GetSprite()
{
	return m_ObjectSprite;
}

char
MapObject::GetTileReprensentation()
{
	return m_tileRepresentation;
}
