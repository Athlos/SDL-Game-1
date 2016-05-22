#include "mapobject.h"
#include "backbuffer.h"
#include <cassert>

MapObject::MapObject()
:m_isCollidable(false)
, m_isBreakable(false)
, m_tileRepresentation('E')
, m_x(0)
, m_y(0)
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
		m_objectSprite = backBuffer.CreateSprite("Assets\\rock.png");
		m_isCollidable = true;
		m_isBreakable = false;
		m_tileRepresentation = TileRepresentation;
		m_objectSprite->SetHeight(64.0f);
		m_objectSprite->SetWidth(64.0f);
		return true;
	case 'B':
		m_objectSprite = backBuffer.CreateSprite("Assets\\pot.png");
		m_isCollidable = false;
		m_isBreakable = true;
		m_tileRepresentation = TileRepresentation;
		m_objectSprite->SetHeight(64.0f);
		m_objectSprite->SetWidth(64.0f);
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
MapObject::SetupCollision(b2World& m_world)
{
	m_objectBodyDef.type = b2_staticBody;
	m_objectBodyDef.position.Set(static_cast<float>(m_x), static_cast<float>(m_y));
	m_objectBodyDef.angle = 0;
	m_objectBody = m_world.CreateBody(&m_objectBodyDef);
	if (m_tileRepresentation == 'B')
	{
		m_objectShape.SetAsBox(m_objectSprite->GetWidth() / 3 * 2, m_objectSprite->GetHeight() / 3 * 2);
	}
	else
	{
		m_objectShape.SetAsBox(m_objectSprite->GetWidth(), m_objectSprite->GetHeight());
	}
	
	m_objectFixtureDef.shape = &m_objectShape;
	m_objectFixtureDef.density = 1;
	m_objectBody->CreateFixture(&m_objectFixtureDef);
	m_objectBody->SetGravityScale(0);
}
void
MapObject::Draw(BackBuffer &backBuffer)
{//if the tile is not equal to an empty tile
	if (m_tileRepresentation != 'E')
	{//draw
		assert(m_objectSprite);
		m_objectSprite->Draw(backBuffer);
	}//otherwise don't
}

void
MapObject::Process(float deltaTime)
{
	//if object is breakable, and the player hits the object break the object
	//spawn coins/hearts and delete object from map.
	if (m_tileRepresentation != 'E')
	{
		m_x = m_objectBodyDef.position.x;
		m_y = m_objectBodyDef.position.y;
		m_objectSprite->SetX(m_objectBodyDef.position.x);
		m_objectSprite->SetY(m_objectBodyDef.position.y);
	}
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
	return m_objectSprite;
}

char
MapObject::GetTileReprensentation()
{
	return m_tileRepresentation;
}

int
MapObject::GetPositionX()
{
	return m_x;
}
int
MapObject::GetPositionY()
{
	return m_y;
}

void
MapObject::SetPositionX(int x)
{
	m_x = x;
	m_objectSprite->SetX(static_cast<float>(m_x));
}

void
MapObject::SetPositionY(int y)
{
	m_y = y;
	m_objectSprite->SetY(static_cast<float>(y));
}

b2BodyDef
MapObject::GetObjectBodyDef()
{
	return m_objectBodyDef;
}