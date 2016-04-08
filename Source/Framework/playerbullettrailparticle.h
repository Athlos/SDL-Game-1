#ifndef __PLAYERBULLETTRAILPARTICLE_H__
#define __PLAYERBULLETTRAILPARTICLE_H__

#include "particle.h"
#include "entity.h"
#include "backbuffer.h"
#include <vector>



class PlayerBulletTrailParticle : public Particle
{
public:
	PlayerBulletTrailParticle();
	~PlayerBulletTrailParticle();
	bool Initialise(Sprite* texture);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	void SpawnParticle(int x, int y, BackBuffer* backbuffer, float duration, ParticleType t);
protected:
private:

	//Member Data:
public:
protected:
private:
protected:
private:

};
#endif //__PLAYERBULLETTRAILPARTICLE_H__