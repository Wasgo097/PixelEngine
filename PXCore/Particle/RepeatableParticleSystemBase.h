#pragma once
#include "ParticleSystemBase.h"
#include "PXUtilities/Interfaces/ITimeObserver.h"
#include "PXSettings/RepeatableParticleSystemSettings.h"
namespace Core::Particle {
	class RepeatableParticleSystemBase : public ParticleSystemBase, public ITimeObserver {
	public:
		RepeatableParticleSystemBase(const Settings::ParticleSystemSettings& settings,const Settings::RepeatableParticleSystemSettings& repeatable_settings);
		virtual void SecondPassed(unsigned int second) override;
		virtual void MinutePassed(unsigned int minute) override {}
	protected:
		Settings::RepeatableParticleSystemSettings _repeatable_settings;
		std::optional<unsigned int> _init_tick{};
	};
}