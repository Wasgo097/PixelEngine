#pragma once
#include "PXUtilities/Interfaces/ILoopingThread.h"
#include "PXUtilities/ThreadingResource.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>
#include <thread>
#include "PXParticle/RepeatableParticleSystemBase.h"
#include "PXCore/Time/TimeManager.h"
namespace Core::World {
	class WorldBase;
}
namespace Core::Particle{
	class ParticleEmitter :public ILoopingThread {
	public:
		ParticleEmitter(World::WorldBase* parent);
		virtual ~ParticleEmitter();
		void Tick(float time);
		void Draw(sf::RenderWindow& window);
		void PushNewParticles(std::unique_ptr<::Particle::ParticleSystemBase>&& particle_system);
		// Inherited via ILoopingThread
		virtual void Run() override;
		virtual void Wait() override;
		virtual void Terminate() override;
	protected:
		World::WorldBase* _parent;
		Utility::ThreadingResourceLight<std::vector<std::unique_ptr<::Particle::ParticleSystemBase>>> _particles_systems;
		Core::Time::TimeManager _time_manager;
		std::unique_ptr<std::thread> _thr;
		bool _refresh_particles_systems{ true };
	};
}