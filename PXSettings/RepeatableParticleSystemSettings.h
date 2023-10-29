#pragma once
#include <optional>
namespace Settings {
	struct RepeatableParticleSystemSettings {
		RepeatableParticleSystemSettings(unsigned int particle_per_tick, std::optional<int> max_counter) :particle_per_tick{ particle_per_tick }, tick_counter{ max_counter } {}
		bool operator==(const RepeatableParticleSystemSettings& obj)const {
			return particle_per_tick == obj.particle_per_tick and tick_counter == obj.tick_counter;
		}
		unsigned int particle_per_tick = 0;
		//how many times particle system will emit new particles 
		std::optional<int> tick_counter;
	};
}