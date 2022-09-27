#include "RepeatableParticleSystemBase.h"
namespace Core::Particle {
	RepeatableParticleSystemBase::RepeatableParticleSystemBase(const Settings::ParticleSystemSettings& settings, const Settings::RepeatableParticleSystemSettings& repeatable_settings) :
		ParticleSystemBase(settings), _repeatable_settings{ repeatable_settings } {
	}
	void RepeatableParticleSystemBase::SecondPassed(unsigned int second) {
		_add_new_particles = true;
	}
	void RepeatableParticleSystemBase::Tick(float delta) {
		ParticleSystemBase::Tick(delta);
		if (_add_new_particles) {
			if (!_repeatable_settings.tick_counter) {
				AddParticles(_repeatable_settings.particle_per_tick);
			}
			else {
				if (!_init_tick)
					_init_tick = 1;
				else
					(*_init_tick)++;
				if (*_init_tick <= _repeatable_settings.tick_counter) {
					AddParticles(_repeatable_settings.particle_per_tick);
				}
			}
			_add_new_particles = false;
		}
	}
}