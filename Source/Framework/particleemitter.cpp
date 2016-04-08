#include "particleemitter.h"
#include "particle.h"
#include "backbuffer.h"
#include "logmanager.h"

#include <cmath>
#include <ctime>
#include <cassert>

ParticleEmitter::ParticleEmitter() {
	srand(time(0));
}

ParticleEmitter::~ParticleEmitter() {

}

void ParticleEmitter::SpawnNewParticles(int x, int y, int amount, BackBuffer* backbuffer, ParticleType t) {
	PlayerBulletTrailParticle* playerP;
	if (x <= 0) {
		LogManager::GetInstance().Log("emitter received zero");
	}
	for (int i = 0; i < amount; i++) {
			switch (t){
			case PLAYERBULLETTRAIL:
				playerP = new PlayerBulletTrailParticle();
				playerP->SpawnParticle(x, y, backbuffer, 0.5, t);
				m_particles.push_back(playerP);
				break;
			default:
				break;
			}
	}
	
}

void ParticleEmitter::Process(float deltaTime) {

	std::vector<Particle*>::iterator iter = m_particles.begin();

	while (iter != m_particles.end()) {
		Particle* current = *iter;
		if (current->GetAge() <= 0) {
			iter = m_particles.erase(iter);
			delete current;
		}
		else {
			current->Process(deltaTime);
			iter++;



		}
	}


}
void ParticleEmitter::Draw(BackBuffer& backBuffer) {
	for each(Particle* p in m_particles) {
		p->Draw(backBuffer);
	}
}