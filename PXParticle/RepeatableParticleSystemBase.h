#pragma once
#include "ParticleSystemBase.h"
#include <atomic>
#include "PXUtilities/Interfaces/ITimeObserver.h"
#include "PXSettings/RepeatableParticleSystemSettings.h"
namespace Particle {
	class RepeatableParticleSystemBase : public ParticleSystemBase, public ITimeObserver {
	public:
		RepeatableParticleSystemBase(const Settings::ParticleSystemSettings& settings, const Settings::RepeatableParticleSystemSettings& repeatable_settings);
		virtual void SecondPassed(unsigned int second) override;
		virtual void MinutePassed(unsigned int minute) override {}
		virtual void Tick(float delta)override;
	protected:
		Settings::RepeatableParticleSystemSettings _repeatable_settings;
		std::optional<unsigned int> _current_tick;
		std::atomic_bool _add_new_particles{ false };
	};
}