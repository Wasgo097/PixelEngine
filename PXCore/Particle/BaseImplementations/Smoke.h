#pragma once
#include "../RepeatableParticleSystemBase.h"
#include "PXFactory/ParticleSystemSettingsFactory.h"
namespace Core::Particle {
	class Smoke :public RepeatableParticleSystemBase {
	public:
		Smoke(const sf::Vector2f& position, Factory::ParticleSystemSettings::Size size = Factory::ParticleSystemSettings::Size::small);
		virtual void InitParticleSystem() override;
	protected:
		virtual std::unique_ptr<Particle> CreateParticle()const;
	};
}