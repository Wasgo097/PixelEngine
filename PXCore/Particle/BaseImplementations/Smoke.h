#pragma once
#include "../ParticleSystemBase.h"
#include "PXFactory/ParticleSystemSettingsFactory.h"
namespace Core::Particle {
	class Smoke :public ParticleSystemBase {
	public:
		Smoke(ParticleEmitter* parent, unsigned int particles,const sf::Vector2f& position, Factory::ParticleSystemSettings::Size size = Factory::ParticleSystemSettings::Size::small);
		virtual void InitParticleSystem() {};
		virtual void EndParticleSystem() {};
	protected:
		virtual std::unique_ptr<Particle> CreateParticle()const;
	};
}