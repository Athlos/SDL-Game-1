#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "particle.h"
#include "entity.h"
#include "playerbullettrailparticle.h"
#include <vector>



class ParticleEmitter : public Entity
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	void SpawnNewParticles(int x, int y, int amount, BackBuffer* backbuffer, ParticleType T);
	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
protected:
private:

	//Member Data:
public:
protected:
	std::vector<Particle*> m_particles;
private:

};
#endif //__PARTICLEEMITTER_H__