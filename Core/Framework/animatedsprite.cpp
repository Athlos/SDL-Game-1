// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include <cassert>

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
{

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
	// Ex007.1: Add the x and y coordinate to the frame coordinate container.
	frames.push_back(x);
	frames.push_back(y);
}

void
AnimatedSprite::Process(float deltaTime)
{
	// Ex007.1: If not paused...
	if (m_paused)
		return;
	// Ex007.1: Count the time elapsed.
	m_timeElapsed += deltaTime;
	// Ex007.1: If the time elapsed is greater than the frame speed.
	// Ex007.1: Reset the time elapsed counter.
	// Ex007.1: If the current frame is greater than the number 
	//          of frames in this animation...
	if (m_timeElapsed > m_frameSpeed)
	{
		if (m_currentFrame >= frames.size() - 2 && m_loop)
		{
			m_currentFrame = 0;
		}
		else if (m_currentFrame < frames.size() - 2)
		{
			m_currentFrame += 2;
		}
		else
		{
			m_animating = false;
		}
		m_timeElapsed = 0;
	}
	if (!m_loop)
		return;
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this, frames[m_currentFrame], frames[m_currentFrame + 1]);
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