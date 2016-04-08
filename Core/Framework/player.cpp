#include "player.h"

#include "sprite.h"
#include "backbuffer.h"
#include <cassert>

Player::Player()
: m_animSprite(0)
{
	Entity::Entity();
	m_x = 400;
	m_y = 560;
}

Player::~Player()
{
}
bool
Player::Initialise(AnimatedSprite* p_animSprite)
{
	assert(p_animSprite);
	m_animSprite = p_animSprite;
	m_animSprite->SetY(static_cast<int>(m_y));
	m_animSprite->SetX(static_cast<int>(m_x));
	return (true);
}

void Player::Process(float deltaTime)
{
	m_animSprite->SetX(static_cast<int>(m_x));
	m_animSprite->SetY(static_cast<int>(m_y));

	m_x += deltaTime * m_velocityX;
	m_y += deltaTime * m_velocityY;
	m_animSprite->SetFrameSpeed(0.08f);
	m_animSprite->Process(deltaTime);
}

void Player::Draw(BackBuffer& backBuffer)
{
	assert(m_animSprite);
	m_animSprite->Draw(backBuffer);
}

void
Player::SetPositionX(float x)
{
	m_x = x;
	m_animSprite->SetX(static_cast<int>(m_x));

}
void
Player::SetPositionY(float y)
{
	m_y = y;
	m_animSprite->SetY(static_cast<int>(m_y));
}
