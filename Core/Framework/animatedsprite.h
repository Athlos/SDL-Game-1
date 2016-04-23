#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"
#include "SDL.h"
#include "direction.h"
#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x, int y);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);

	void TogglePause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

	void LoadFrames(int width);

	void UpdateDirection(Direction dir);

protected:

private:

	// Fields:
public:

protected:


	//std::vector<SDL_Point*> m_frames;

	//Store arrays for all directions - not a great solution sadly
	std::vector<SDL_Point*> m_upFrames;
	std::vector<SDL_Point*> m_downFrames;
	std::vector<SDL_Point*> m_leftFrames;
	std::vector<SDL_Point*> m_rightFrames;

	Direction m_currentDirection;


	float m_frameSpeed;
	int m_frameWidth;

	float m_timeElapsed;
	int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif // __ANIMATEDSPRITE_H__