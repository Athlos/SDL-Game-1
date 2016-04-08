#ifndef __PLAYER_H__
#define __PLAYER_H__

//Class declarations
#include "entity.h"
#include "animatedsprite.h"
#include "backbuffer.h"

class Player : Entity
{
public:
	Player();
	~Player();
	bool Initialise(AnimatedSprite* p_animSprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void SetPositionX(float x);
	void SetPositionY(float y);
protected:
private:

public:
protected:
private:
	AnimatedSprite* m_animSprite;
	int m_x;
	int m_y;
};

#endif //__PLAYER_H__
