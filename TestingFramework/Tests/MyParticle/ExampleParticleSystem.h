#pragma once
#include "PXCore/Particle/ParticleSystemBase.h"
namespace Test {
	class ExampleParticleSystem : public Core::Particle::ParticleSystemBase {
	public:
		ExampleParticleSystem(const Settings::ParticleSystemSettings& settings) :ParticleSystemBase{ settings } {}
		virtual void InitParticleSystem()override;
		//virtual void EndParticleSystem()override {};
	protected:
		virtual std::unique_ptr<Core::Particle::Particle> CreateParticle(Randomizer& randomizer) const override;
	};
}