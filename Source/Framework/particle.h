#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "entity.h"

#include <cmath>
#include <ctime>

enum ParticleType
{
	ALIENEXPLOSION,
	PLAYERBULLETTRAIL,
	BEAMTRAIL,
	BRICKPARTICLE
};

class Particle : public Entity
{
public:
	Particle();
	~Particle();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void SetAccelerationX(float x);
	void SetAccelerationY(float y);
	float GetAge();
	void SetAge(float age);
	void SpawnParticle(int x, int y, BackBuffer* backbuffer);
	ParticleType GetType();
protected:
private:

	//Member Data:
public:
protected:
	float m_accelerationX;
	float m_accelerationY;
	float m_age;
	ParticleType m_type;
private:

};
#endif //__PARTICLE_H__

