#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

class AnimatedSprite;
class Sprite;
class BackBuffer;
class Texture;
class Entity;

#include "entity.h"


class Explosion : public Entity
{
public:
	Explosion();
	~Explosion();
	void Explosion::SetPosition(float x, float y);
	void Explosion::Draw(BackBuffer& backBuffer);
	bool Explosion::Initialise(AnimatedSprite* sprite);
	void Explosion::Process(float deltaTime);
protected:
private:

	//Member Data:
public:
protected:
	AnimatedSprite* m_pSprite;
private:
	
};
#endif //__EXPLOSION_H__

