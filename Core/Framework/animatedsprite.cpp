// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include "direction.h"
#include <cassert>

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.1f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
{
	//enum works yay
	Direction dr = Direction::DOWN;
}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x, int y)
{
	SDL_Point* newPoint = new SDL_Point();
	newPoint->x = x;
	newPoint->y = y;
	m_frames.push_back(newPoint);

}

void
AnimatedSprite::Process(float deltaTime)
{

	if (m_paused)
		return;

	m_timeElapsed += deltaTime;

	if (m_timeElapsed >= m_frameSpeed)
	{
		if (m_currentFrame >= m_frames.size() - 1 && m_loop)
		{
			m_currentFrame = 0;
		}
		else if (m_currentFrame < m_frames.size() - 1)
		{
			m_currentFrame++;
		}
		else
		{
			m_animating = false;
		}
		m_timeElapsed = 0.0f;
	}
	if (!m_loop)
		return;
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this, m_frames[m_currentFrame]->x, m_frames[m_currentFrame]->y);
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::TogglePause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

void AnimatedSprite::LoadFrames(int width)
{
	//Set the center to half the width and height
	SetCenter(width/2, width/2);

	//Set width and height to the same value, assuming your sprite is a square
	m_width = width;
	m_height = width;
	
	//loops by default
	m_loop = true;


	//Grab the texture, and grab frames the size of the width for 1 row
	for (int i = 0; i < m_pTexture->GetWidth(); i += width)
	{
		//Store frame coordinates in m_frames to render later
		SDL_Point* newFrame = new SDL_Point();
		newFrame->x = i;
		newFrame->y = 0;
		m_frames.push_back(newFrame);
	}
}