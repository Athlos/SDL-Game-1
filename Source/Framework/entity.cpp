// 717310 C++ SDL Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <SDL.h>


// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

// Library includes:
#include <cassert>
#include <SDL.h>


Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

bool Entity::IsDead() const{
	return m_dead;
}

void 
Entity::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	// Ex006.2: Generic position update, based upon velocity (and time).
	m_x += deltaTime * m_velocityX;
	m_y += deltaTime * m_velocityY;
	
	// Ex006.2: Boundary checking and position capping. 
	if (m_x >= 800-m_pSprite->GetWidth()) {
		m_x = (800-m_pSprite->GetWidth());
		m_velocityX = 0;
	}
	if (m_x <= 0) {
		m_x = 0;
		m_velocityX = 0;
	}

	
}

bool Entity::IsClickedOn(int x, int y) {
	int x1 = x + 8;
	int y1 = y + 8;
	int radius1 = 16;
	int radius2 = 16;

	int x2 = m_x + 16;
	int y2 = m_y + 16;

	//compare the distance to combined radii
	if (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < 32)
	{
		return true;
	}

	return (false);
}

void 
Entity::Draw(BackBuffer& backBuffer)
{

	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(int x, int y, int radius)
{


	if (sqrt((x - m_x) * (x - m_x) + (y - m_y) * (y - m_y)) < radius + 16)
	{
		return true;
	}


	return (false); 
}


void Entity::SetPosition(float x, float y) {
	m_x = x;
	m_y = y;
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
}


void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

float 
Entity::GetPositionX()
{
	return (m_x);
}

float 
Entity::GetPositionY()
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}
