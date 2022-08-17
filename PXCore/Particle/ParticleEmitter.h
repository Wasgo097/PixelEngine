#pragma once
#include "PXUtilities/Interfaces/ILoopingThread.h"
#include "PXUtilities/ThreadingResource.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include <thread>
#include "ParticleSystemBase.h"
namespace Core::World {
	class WorldBase;
}
namespace Core::Particle {
	class ParticleEmitter :public ILoopingThread {
	public:
		ParticleEmitter(World::WorldBase* parent);
		void Tick(float time);
		void Draw(sf::RenderWindow& window);
		void PushNewParticles(std::unique_ptr<ParticleSystemBase>&& particle_system);
		// Inherited via ILoopingThread
		virtual void Run() override;
		virtual void Wait() override;
		virtual void Terminate() override;
	protected:
		World::WorldBase* _parent;
		Utility::ThreadingResourceLight<std::vector<std::unique_ptr<ParticleSystemBase>>> _particles_systems;
		std::thread _thr;
		bool _refresh_particles_systems = true;
	};
}