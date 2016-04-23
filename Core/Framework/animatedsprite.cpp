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
	, m_currentDirection(Direction::UP)
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
		if (m_currentFrame >= m_upFrames.size() - 1 && m_loop)
		{
			m_currentFrame = 0;
		}
		else if (m_currentFrame < m_upFrames.size() - 1)
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
	//Use correct directional sprite
	if (m_currentDirection == Direction::UP)
	{
		backbuffer.DrawAnimatedSprite(*this, m_upFrames[m_currentFrame]->x, m_upFrames[m_currentFrame]->y);
	}
	else if (m_currentDirection == Direction::DOWN)
	{
		backbuffer.DrawAnimatedSprite(*this, m_downFrames[m_currentFrame]->x, m_downFrames[m_currentFrame]->y);
	}
	else if (m_currentDirection == Direction::LEFT)
	{
		backbuffer.DrawAnimatedSprite(*this, m_leftFrames[m_currentFrame]->x, m_leftFrames[m_currentFrame]->y);
	}
	else if (m_currentDirection == Direction::RIGHT)
	{
		backbuffer.DrawAnimatedSprite(*this, m_rightFrames[m_currentFrame]->x, m_rightFrames[m_currentFrame]->y);
	}
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
	for (int a = 0; a < m_pTexture->GetHeight(); a += width)
	{
		//Grab the texture, and grab frames the size of the width for 1 row
		for (int i = 0; i < m_pTexture->GetWidth(); i += width)
		{
			//Store frame coordinates to render later
			SDL_Point* newFrame = new SDL_Point();
			newFrame->x = i;
			newFrame->y = a;

			//Choose correct array to store frames in, this is kinda messy for now
			if (a == 0)
			{
				m_downFrames.push_back(newFrame);
			}
			else if (a == width)
			{
				m_leftFrames.push_back(newFrame);
			}
			else if (a == width * 2) 
			{
				m_rightFrames.push_back(newFrame);
			}
			else if (a == width * 3)
			{
				m_upFrames.push_back(newFrame);
			}

		}
	}

	
}

void AnimatedSprite::UpdateDirection(Direction dir)
{
	//If stop, pause animation, else make sure its not paused
	if (dir == Direction::STOP)
	{
		m_paused = true;
		return;
	}
	m_paused = false;

	//Reset animation frames
	if (m_currentDirection == Direction::RESET)
	{
		StartAnimating();
		return;
	}

	//no update if the direction is the same
	if (m_currentDirection == dir)
	{
		return;
	}
		

	//Set the new direction, reset the animation frame and durations
	m_currentDirection = dir;
	StartAnimating();
}