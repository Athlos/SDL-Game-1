#include "mapobject.h"
#include "backbuffer.h"
#include <cassert>
#include <Box2D.h>

MapObject::MapObject()
:m_isCollidable(false)
, m_isBreakable(false)
, m_tileRepresentation('E')
, m_x(0)
, m_y(0)
, m_isColliding(false)
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
		m_isColliding = false;
		m_tileRepresentation = TileRepresentation;
		m_objectSprite->SetHeight(64.0f);
		m_objectSprite->SetWidth(64.0f);
		return true;
	case 'B':
		m_objectSprite = backBuffer.CreateSprite("Assets\\pot.png");
		m_isCollidable = false;
		m_isBreakable = true;
		m_isColliding = false;
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
		m_objectShape.SetAsBox(1, 1);
	}
	m_objectFixtureDef.shape = &m_objectShape;
	m_objectFixtureDef.density = 1;
	m_objectBody->CreateFixture(&m_objectFixtureDef);
	m_objectBody->SetUserData(this);
}
void
MapObject::Draw(BackBuffer &backBuffer)
{
	if (m_tileRepresentation != 'E')
	{//draw
		if (m_isColliding)
		{
			m_objectSprite->SetWidth(32.0f);
			SDL_Log("COLLISION CONFIRMED");
		}
		else
		{
			m_objectSprite->SetWidth(64.0f);
		}
		assert(m_objectSprite);
		m_objectSprite->Draw(backBuffer);
	}//otherwise don't

	if (m_tileRepresentation == 'B')
	{
		backBuffer.DrawRectangleUnfilled(m_objectBody->GetPosition().x, m_objectBody->GetPosition().y, 
			m_objectBody->GetPosition().x + ((2.0f / 3.0f)*64), m_objectBody->GetPosition().y + ((2.0f / 3.0f)*64));
	}
	else
	{
		backBuffer.DrawRectangleUnfilled(m_objectBody->GetPosition().x, m_objectBody->GetPosition().y, 
			m_objectBody->GetPosition().x + 64, m_objectBody->GetPosition().y + 64);
	}
	
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

void
MapObject::StartContact()
{
	m_isColliding = true;
}
void
MapObject::EndContact()
{
	m_isColliding = false;
}