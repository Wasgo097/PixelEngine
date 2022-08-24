#pragma once
#include "PXCore/Particle/ParticleSystemBase.h"
namespace Test {
	class ExampleParticleSystem : public Core::Particle::ParticleSystemBase {
	public:
		ExampleParticleSystem(Core::Particle::ParticleEmitter* parent, const Settings::ParticleSystemSettings& settings) :ParticleSystemBase{ parent,settings } {}
		virtual void InitParticleSystem()override;
		//virtual void EndParticleSystem()override {};
	protected:
		virtual std::unique_ptr<Core::Particle::Particle> CreateParticle() const override;
	};
}