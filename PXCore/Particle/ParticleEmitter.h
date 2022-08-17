#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include "ParticleSystemBase.h"
namespace Core::World {
	class WorldBase;
}
namespace Core::Particle {
	class ParticleEmitter {
	public:
		ParticleEmitter(World::WorldBase* parent);
		void Tick(float time);
		void Draw(sf::RenderWindow& window);
	protected:
		World::WorldBase* _parent;
		std::vector<std::unique_ptr<ParticleSystemBase>> _particles_systems;
	};
}