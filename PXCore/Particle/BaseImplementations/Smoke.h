#pragma once
#include "../ParticleSystemBase.h"
#include "PXFactory/ParticleSystemSettingsFactory.h"
namespace Core::Particle {
	class Smoke :public ParticleSystemBase {
	public:
		Smoke(const sf::Vector2f& position, Factory::ParticleSystemSettings::Size size = Factory::ParticleSystemSettings::Size::small);
		virtual void InitParticleSystem() override;
	protected:
		virtual std::unique_ptr<Particle> CreateParticle()const;
	};
}