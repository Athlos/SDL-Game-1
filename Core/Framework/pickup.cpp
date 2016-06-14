#include "pickup.h"
#include <cassert>


Pickup::Pickup(b2World& world)
{
	m_x = 500;
	m_y = 500;
	m_rawX = m_x;
	m_rawY = m_y;

	//bobbing values
	m_bobX = 5;
	m_bobY = 10;
	m_bobLeftRight = true;
	m_bobUpDown = true;

	//m_velocityX = 60;
	m_isPickedUp = false;

	//default type is heart
	m_type = HEALTH;

	Entity::SetupCollision(world, 8.0f);
}


Pickup::~Pickup()
{
}

bool Pickup::Initialise(AnimatedSprite* p_animSprite)
{
	//Set up player sprite
	assert(p_animSprite);
	m_animSprite = p_animSprite;
	m_animSprite->SetY(static_cast<int>(m_y));
	m_animSprite->SetX(static_cast<int>(m_x));

	return (true);
}

void Pickup::SetPickedUp(bool isPickedUp)
{
	m_isPickedUp = isPickedUp;
}

bool Pickup::IsPickedUp()
{
	return m_isPickedUp;
}

void Pickup::SetPickupType(PickupType type)
{
	m_type = type;
}

PickupType Pickup::GetPickupType()
{
	return m_type;
}

void Pickup::Process(float deltaTime)
{
	/*
	if (m_x >= m_rawX + m_bobX)
	{
		m_velocityX = -60;
	}
	if (m_x <= m_rawX - m_bobX)
	{
		m_velocityX = +60;
	}
	*/

	m_animSprite->SetX(static_cast<int>(m_x));
	m_animSprite->SetY(static_cast<int>(m_y));

	m_x += (static_cast<int>(deltaTime * m_velocityX));
	m_y += (static_cast<int>(deltaTime * m_velocityY));
	m_animSprite->Process(deltaTime);
}

void Pickup::Draw(BackBuffer& backBuffer)
{
	if (m_isPickedUp)
		return;
	assert(m_animSprite);
	m_animSprite->Draw(backBuffer);
	backBuffer.DrawRectangleUnfilled(m_x, m_y, m_x + 64, m_y + 64);
}

void Pickup::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	m_animSprite->SetX(static_cast<int>(m_x));
	m_animSprite->SetY(static_cast<int>(m_y));
}
